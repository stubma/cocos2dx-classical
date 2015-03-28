/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "CCTMXMapInfo.h"
#include "CCTMXTileSetInfo.h"

NS_CC_BEGIN

CCTMXMapInfo::CCTMXMapInfo() {
}

CCTMXMapInfo::~CCTMXMapInfo() {
}

CCTMXMapInfo* CCTMXMapInfo::create() {
	CCTMXMapInfo* m = new CCTMXMapInfo();
	CC_SAFE_AUTORELEASE_RETURN(m, CCTMXMapInfo*);
}

string CCTMXMapInfo::getProperty(const string& key) {
	CCString* p = (CCString*)m_properties.objectForKey(key);
	if(p)
		return p->getCString();
	else
		return "";
}

void CCTMXMapInfo::addProperty(const string& key, const string& value) {
	if(!m_properties.objectForKey(key)) {
		m_properties.setObject(CCString::create(value), key);
	}
}

int CCTMXMapInfo::getTileSetIndex(int gid) {
	int pureGid = gid & kCCTMXTileFlagFlipMask;
	int count = m_tilesets.count();
	for(int i = 0; i < count; i++) {
		CCTMXTileSetInfo* tileset = (CCTMXTileSetInfo*)m_tilesets.objectAtIndex(i);
		if(tileset->getFirstGid() > pureGid)
			return i - 1;
	}
	return m_tilesets.count() - 1;
}

string CCTMXMapInfo::getTileProperty(int gid, const string& key) {
	int pureGid = gid & kCCTMXTileFlagFlipMask;
	char buf[32];
	sprintf(buf, "%d", pureGid);
	CCDictionary* props = (CCDictionary*)m_tileProperties.objectForKey(buf);
	if(props) {
		CCString* p = (CCString*)props->objectForKey(key);
		if(p)
			return p->getCString();
		else
			return "";
	} else {
		return "";
	}
}

CCDictionary* CCTMXMapInfo::getTileProperties(int gid) {
    char buf[32];
    sprintf(buf, "%d", gid);
    return (CCDictionary*)m_tileProperties.objectForKey(buf);
}

void CCTMXMapInfo::addTileProperty(int gid, const string& key, const string& value) {
	int pureGid = gid & kCCTMXTileFlagFlipMask;
	char buf[32];
	sprintf(buf, "%d", pureGid);
	CCDictionary* props = (CCDictionary*)m_tileProperties.objectForKey(buf);
	if(!props) {
		props = CCDictionary::create();
		m_tileProperties.setObject(props, buf);
	}
	props->setObject(CCString::create(value), key);
}
	
NS_CC_END
