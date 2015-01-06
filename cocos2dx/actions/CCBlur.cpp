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
#include "CCBlur.h"
#include "shaders/CCShaders.h"
#include "ccTypes.h"

NS_CC_BEGIN

CCBlur::CCBlur() :
m_oldProgram(nullptr) {
}

CCBlur::~CCBlur() {
}

CCBlur* CCBlur::create(float duration, CCSize startBlurSize, CCSize endBlurSize) {
    CCBlur* a = new CCBlur();
    a->initWithBlurSize(duration, startBlurSize, endBlurSize);
    CC_SAFE_AUTORELEASE_RETURN(a, CCBlur*);
}

bool CCBlur::initWithBlurSize(float d, CCSize startBlurSize, CCSize endBlurSize) {
    setDuration(d);
    m_startBlurSize = CCS2ccs(startBlurSize);
	m_endBlurSize = CCS2ccs(endBlurSize);
	m_deltaBlurSize = ccSizeMake(m_endBlurSize.width - m_startBlurSize.width,
                                 m_endBlurSize.height - m_startBlurSize.height);
    
    return true;
}

void CCBlur::update(float time) {
    ccCustomUniformValue& v = m_pTarget->getCustomUniformValue();
    v.blur.blurSize.width = m_startBlurSize.width + m_deltaBlurSize.width * time;
    v.blur.blurSize.height = m_startBlurSize.height + m_deltaBlurSize.height * time;
}

void CCBlur::startWithTarget(CCNode *pTarget) {
    CCActionInterval::startWithTarget(pTarget);
    
    // save old program
    if(!m_oldProgram) {
        m_oldProgram = pTarget->getShaderProgram();
    }
    
    // set new program
    ccCustomUniformValue v = {
        .blur = {
            CCS2ccs(pTarget->getContentSize()),
            m_startBlurSize,
            cc4fTRANSPARENT
        }
    };
    pTarget->setShaderProgram(CCShaders::programForKey(kCCShader_blur), v);
}

void CCBlur::stop() {
    getTarget()->setShaderProgram(m_oldProgram);
    CCActionInterval::stop();
}

CCObject* CCBlur::copyWithZone(CCZone *pZone) {
    CCZone* pNewZone = nullptr;
    CCBlur* pCopy = nullptr;
    if(pZone && pZone->m_pCopyObject) {
        // in case of being called at sub class
        pCopy = (CCBlur*)(pZone->m_pCopyObject);
    } else {
        pCopy = new CCBlur();
        pZone = pNewZone = new CCZone(pCopy);
        CC_SAFE_AUTORELEASE(pCopy);
    }
	
    CCActionInterval::copyWithZone(pZone);
    pCopy->initWithBlurSize(m_fDuration, ccs2CCS(m_startBlurSize), ccs2CCS(m_endBlurSize));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCActionInterval* CCBlur::reverse() {
    return CCBlur::create(getDuration(), ccs2CCS(m_endBlurSize), ccs2CCS(m_startBlurSize));
}

NS_CC_END