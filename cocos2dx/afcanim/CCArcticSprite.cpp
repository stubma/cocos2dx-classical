/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-better
 
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
#include "CCArcticSprite.h"
#include "CCArcticManager.h"
#include <stdarg.h>

NS_CC_BEGIN

CCArcticSprite::CCArcticSprite() :
		m_arctic(nullptr) {
}

CCArcticSprite::~CCArcticSprite() {
	CC_SAFE_RELEASE(m_arctic);
}

CCArcticSprite* CCArcticSprite::create(const char* path, int animIndex, CCTexture2D** tex, int count) {
	// create arctic sprite
	CCArcticSprite* sprite = new CCArcticSprite();

	// load anu file data
	sprite->m_arctic = CCArcticManager::getInstance()->load(path);
	CC_SAFE_RETAIN(sprite->m_arctic);

	// add others
	for(int i = 0; i < count; i++) {
		CCSpriteBatchNode* sheet = CCAFCSprite::createBatchNode(tex[i]);
		sprite->m_sheetList.push_back(sheet);
		CC_SAFE_RETAIN(sheet);
	}

	// start animation
	sprite->playAnimation(animIndex);

	// return
	CC_SAFE_AUTORELEASE(sprite);
	return sprite;
}

CCArcticSprite* CCArcticSprite::create(const char* path, int animIndex, CCTexture2D* tex, ...) {
	// create arctic sprite
	CCArcticSprite* sprite = new CCArcticSprite();

	// load anu file data
	sprite->m_arctic = CCArcticManager::getInstance()->load(path);
	CC_SAFE_RETAIN(sprite->m_arctic);

	va_list textures;
	va_start(textures, tex);

	// add first
	CCSpriteBatchNode* sheet = CCAFCSprite::createBatchNode(tex);
	sprite->m_sheetList.push_back(sheet);
	CC_SAFE_RETAIN(sheet);

	// add others
	for(CCTexture2D* t = va_arg(textures, CCTexture2D*); t != nullptr; t = va_arg(textures, CCTexture2D*)) {
		sheet = CCAFCSprite::createBatchNode(t);
		sprite->m_sheetList.push_back(sheet);
		CC_SAFE_RETAIN(sheet);
	}

	va_end(textures);

	// start animation
	sprite->playAnimation(animIndex);

	// return
	CC_SAFE_AUTORELEASE(sprite);
	return sprite;
}

CCAFCAnimation* CCArcticSprite::getAnimationAt(int index, CCAFCClipMapping* mapping) {
	if(index < 0 || index >= getAnimationCount())
		return nullptr;
	else
		return CCArcticManager::getInstance()->getAnimationData(m_arctic, index, mapping);
}

int CCArcticSprite::getAnimationCount() {
	return m_arctic->m_animationCount;
}

int CCArcticSprite::getImageCount() {
	return 1;
}

NS_CC_END