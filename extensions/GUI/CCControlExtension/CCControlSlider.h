/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot. All rights reserved.
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
 */


#ifndef __CCCONTROL_SLIDER_H__
#define __CCCONTROL_SLIDER_H__

#include "CCControl.h"
#include "CCInvocation.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 *
 * A slider control whose value can vary between min and max value. The value
 * can be changed in consecutive or discrete mode.
 *
 * \par
 * Slider is composited by background, thumb, and progress. The progress is optional.
 * If progress is present, it must have same size of background
 *
 * \note
 * There is CCControlSlider in cocos2d-x extensions, but it doesn't support consecutive
 * mode. I copied its code and enhanced it for a better slider.
 */
class CC_EX_DLL CCControlSlider : public CCControl {
protected:
    CCControlSlider();
    
    /// init slider
    virtual bool initWithSprites(CCSprite* bg, CCSprite* thumb, CCSprite* progress);
    
    /// update thumb and progress when value is changed
    void updateSpritesForValueChange();
    
    /// update layout
    void updateLayout();
    
    /// is touch in slider bounding box
    bool isTouchInside(CCTouch* touch);
    
    /// touch location in self space
    CCPoint locationFromTouch(CCTouch* touch);
    
    // event method
    void sliderBegan(CCPoint location);
    void sliderMoved(CCPoint location);
    void sliderEnded(CCPoint location);
    
    /// Returns the value for the given location
    float valueForLocation(CCPoint location);
    
public:
    virtual ~CCControlSlider();
    static CCControlSlider* create(CCSprite* bg, CCSprite* thumb, CCSprite* progress = NULL);
    
    // override
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    virtual void needsLayout() { updateSpritesForValueChange(); }
    
    // values
    CC_SYNTHESIZE_SETTER(float, m_value, Value);
    CC_SYNTHESIZE_READONLY(int, m_intValue, IntValue);
    CC_SYNTHESIZE_SETTER(float, m_minimumValue, MinimumValue);
    CC_SYNTHESIZE_SETTER(float, m_maximumValue, MaximumValue);
    CC_SYNTHESIZE(float, m_minimumAllowedValue, MinimumAllowedValue);
    CC_SYNTHESIZE(float, m_maximumAllowedValue, MaximumAllowedValue);
    
    // discrete mode
    CC_SYNTHESIZE_BOOL(m_discreteMode, DiscreteMode);
    
    // components
    CC_SYNTHESIZE_SETTER(CCSprite*, m_thumbSprite, ThumbSprite);
    CC_SYNTHESIZE_SETTER(CCSprite*, m_progressSprite, ProgressSprite);
    CC_SYNTHESIZE_SETTER(CCSprite*, m_backgroundSprite, BackgroundSprite);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif