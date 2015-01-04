/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Converted to c++ / cocos2d-x by Angus C
*
 */

#include "CCControlSlider.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCDirector.h"

NS_CC_EXT_BEGIN

CCControlSlider::CCControlSlider() :
m_thumbSprite(nullptr),
m_backgroundSprite(nullptr),
m_progressSprite(nullptr),
m_value(0),
m_intValue(0),
m_minimumValue(0),
m_maximumValue(1),
m_minimumAllowedValue(0),
m_maximumAllowedValue(1),
m_discreteMode(false) {
}

CCControlSlider::~CCControlSlider() {
    
}

CCControlSlider* CCControlSlider::create(CCSprite* bg, CCSprite* thumb, CCSprite* progress) {
    CCControlSlider* s = new CCControlSlider();
    if(s->initWithSprites(bg, thumb, progress)) {
        return (CCControlSlider*)s->autorelease();
    }
    
    CC_SAFE_RELEASE(s);
    return nullptr;
}

bool CCControlSlider::initWithSprites(CCSprite* bg, CCSprite* thumb, CCSprite* progress) {
    if(!CCControl::init())
        return false;
    
    // add component
    m_backgroundSprite = bg;
    m_thumbSprite = thumb;
    m_progressSprite = progress;
    addChild(m_backgroundSprite);
    if(m_progressSprite)
        addChild(m_progressSprite, 1);
    addChild(m_thumbSprite, 2);
    
    // update
    updateLayout();
    
    // trigger first value change event
    setValue(m_minimumValue);
    
    // event
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    return true;
}

void CCControlSlider::setBackgroundSprite(CCSprite* bg) {
    CCAssert(bg != nullptr, "Slider background can't be nullptr");
    
    // remove old and add new
    if(m_backgroundSprite) {
        m_backgroundSprite->removeFromParent();
        m_backgroundSprite = nullptr;
    }
    m_backgroundSprite = bg;
    addChild(m_backgroundSprite);
    
    // necessary update
    updateLayout();
    updateSpritesForValueChange();
}

void CCControlSlider::setThumbSprite(CCSprite* thumb) {
    CCAssert(thumb != nullptr, "Slider thumb can't be nullptr");
    
    // remove old and add new
    if(m_thumbSprite) {
        m_thumbSprite->removeFromParent();
        m_thumbSprite = nullptr;
    }
    m_thumbSprite = thumb;
    addChild(m_backgroundSprite, 2);
    
    // necessary update
    updateLayout();
    updateSpritesForValueChange();
}

void CCControlSlider::setProgressSprite(CCSprite* progress) {
    // remove old and add new
    if(m_progressSprite) {
        m_progressSprite->removeFromParent();
        m_progressSprite = nullptr;
    }
    m_progressSprite = progress;
    addChild(m_progressSprite, 1);
    
    // necessary update
    updateLayout();
    updateSpritesForValueChange();
}

void CCControlSlider::setValue(float v) {
    m_value = clampf(v, m_minimumValue, m_maximumValue);
    if(m_discreteMode) {
        int intValue = (int)(m_value + 0.5f);
        if(m_intValue != intValue) {
            m_intValue = intValue;
            m_value = intValue;
            updateSpritesForValueChange();
            sendActionsForControlEvents(CCControlEventValueChanged);
        }
    } else {
        m_intValue = (int)m_value;
        updateSpritesForValueChange();
        sendActionsForControlEvents(CCControlEventValueChanged);
    }
}

void CCControlSlider::setMinimumValue(float min) {
    m_minimumValue = min;
    m_minimumAllowedValue = min;
    if(m_minimumValue >= m_maximumValue) {
        m_maximumValue = m_minimumValue + 1.0f;
    }
    setValue(m_value);
}

void CCControlSlider::setMaximumValue(float max) {
    m_maximumValue = max;
    m_maximumAllowedValue = max;
    if(m_maximumValue <= m_minimumValue) {
        m_minimumValue = m_maximumValue - 1.0f;
    }
    setValue(m_value);
}

void CCControlSlider::updateLayout() {
    // self
    CCSize bgSize = m_backgroundSprite->getContentSize();
    CCSize thumbSize = m_thumbSprite->getContentSize();
    CCSize size = CCSizeMake(bgSize.width,
                             MAX(bgSize.height, thumbSize.height));
    setContentSize(size);
    setAnchorPoint(ccp(0.5f, 0.5f));
    ignoreAnchorPointForPosition(false);
    
    // background
    m_backgroundSprite->ignoreAnchorPointForPosition(false);
    m_backgroundSprite->setAnchorPoint(ccp(0.5f, 0.5f));
    m_backgroundSprite->setPosition(ccp(size.width / 2, size.height / 2));
    
    // the progress bar
    if(m_progressSprite) {
        m_progressSprite->ignoreAnchorPointForPosition(false);
        m_progressSprite->setAnchorPoint(ccp(0, 0.5f));
        m_progressSprite->setPosition(ccp(0, size.height / 2));
    }
    
    // thumb
    m_thumbSprite->ignoreAnchorPointForPosition(false);
    m_thumbSprite->setPosition(ccp(0.0f, size.height / 2));
}

void CCControlSlider::updateSpritesForValueChange() {
    // update thumb position for new value
    if(m_thumbSprite) {
        float percent = (m_value - m_minimumValue) / (m_maximumValue - m_minimumValue);
        CCPoint pos = m_thumbSprite->getPosition();
        pos.x = percent * m_backgroundSprite->getContentSize().width;
        m_thumbSprite->setPosition(pos);
        
        // Stretches content proportional to newLevel
        if(m_progressSprite) {
            CCRect textureRect = m_progressSprite->getTextureRect();
            textureRect = CCRectMake(textureRect.origin.x, textureRect.origin.y, pos.x, textureRect.size.height);
            m_progressSprite->setTextureRect(textureRect, m_progressSprite->isTextureRectRotated(), textureRect.size);
        }
    }
}

bool CCControlSlider::isTouchInside(CCTouch* touch) {
    // location in parent space
    CCPoint touchLocation = touch->getLocation();
    touchLocation = getParent()->convertToNodeSpace(touchLocation);
    
    // rect in parent space
    CCRect rect = boundingBox();
    
    // check contain or not
    return rect.containsPoint(touchLocation);
}

CCPoint CCControlSlider::locationFromTouch(CCTouch* touch) {
    // location in self space
    CCPoint touchLocation = touch->getLocation();
    touchLocation = convertToNodeSpace(touchLocation);
    
    // clamp
    touchLocation.x = clampf(touchLocation.x, 0, m_backgroundSprite->getContentSize().width);
    
    // return
    return touchLocation;
}

bool CCControlSlider::ccTouchBegan(CCTouch* touch, CCEvent* pEvent) {
    if(!isTouchInside(touch)) {
        return false;
    }
    
    CCPoint location = locationFromTouch(touch);
    sliderBegan(location);
    return true;
}

void CCControlSlider::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
    CCPoint location = locationFromTouch(pTouch);
    sliderMoved(location);
}

void CCControlSlider::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent) {
    sliderEnded(CCPointZero);
}

void CCControlSlider::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
    sliderEnded(CCPointZero);
}

float CCControlSlider::valueForLocation(CCPoint location) {
    float percent = location.x / m_backgroundSprite->getContentSize().width;
    return MAX(MIN(m_minimumValue + percent * (m_maximumValue - m_minimumValue), m_maximumAllowedValue),
               m_minimumAllowedValue);
}

void CCControlSlider::sliderBegan(CCPoint location) {
    setSelected(true);
    getThumbSprite()->setColor(ccGRAY);
    setValue(valueForLocation(location));
}

void CCControlSlider::sliderMoved(CCPoint location) {
    setValue(valueForLocation(location));
}

void CCControlSlider::sliderEnded(CCPoint location) {
    if (isSelected()) {
        setValue(valueForLocation(m_thumbSprite->getPosition()));
    }
    getThumbSprite()->setColor(ccWHITE);
    setSelected(false);
}

NS_CC_EXT_END
