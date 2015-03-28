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
#ifndef __CCTMXObjectDebugRenderer_h__
#define __CCTMXObjectDebugRenderer_h__

#include "base_nodes/CCNode.h"
#include "cocoa/CCPointList.h"

NS_CC_BEGIN

class CCTMXTiledMap;

/**
 * Debug layer for rendering tmx objects
 */
class CCTMXObjectDebugRenderer : public CCNode {
protected:
	CCTMXObjectDebugRenderer();
	
public:
	virtual ~CCTMXObjectDebugRenderer();
	static CCTMXObjectDebugRenderer* create(CCTMXTiledMap* m);
	
	// init
	virtual bool initWithMap(CCTMXTiledMap* map);
	
	// override super
	virtual void draw();
	
	// tmx tile map
	CC_SYNTHESIZE(CCTMXTiledMap*, m_map, Map);
	
	// point buffer
	CC_SYNTHESIZE(CCPointList, m_vertices, Vertices);
};

NS_CC_END

#endif // __CCTMXObjectDebugRenderer_h__
