//
//	CCSuperAnimV2.h
//
//  Created by Raymond Lu(Raymondlu1105@qq.com)
//  
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
#ifndef CCSuperAnim_H
#define CCSuperAnim_H

#include "cocos2d.h"
#include "CCSuperAnimCommon.h"
#include "ExtensionMacros.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

class CCSuperAnimListener
{
public:
    virtual void OnAnimSectionEnd(int theId, std::string theLabelName){}
    virtual void OnTimeEvent(int theId, std::string theLabelName, int theEventId){}
};

/**
 * to handle event in lua side, you need add a lua function handler looks like below
     function XXX:onSuperAnimEvent(sa, e, id, label, ...)
        if e == cc.SuperAnimEventTime then
            -- for time event, has event id arg
            local eventId = ...
        elseif e == cc.SuperAnimEventEnd then
        end
     end
 */
class CCSuperAnim : public CCNode
{
private:
    int mId;
    CCSuperAnimListener *mListener;
    SuperAnimHandler mAnimHandler;
    bool mIsLoop;
    int mAnimState;
    // support sprite sheet
    std::string mSpriteSheetFileFullPath;
    bool mUseSpriteSheet;
    CCTexture2D* mSpriteSheet;
    bool mIsFlipX;
    bool mIsFlipY;
    float mSpeedFactor;
    
    
    typedef std::map<SuperAnimSpriteId, SuperAnimSpriteId> SuperSpriteIdToSuperSpriteIdMap;
    SuperSpriteIdToSuperSpriteIdMap mReplacedSpriteMap;
    
    // for time event
    struct TimeEventInfo{
        std::string mLabelName;
        float mTimeFactor;
        int mEventId;
    };
    typedef std::vector<TimeEventInfo> TimeEventInfoArray;
    typedef std::map<std::string, TimeEventInfoArray> LabelNameToTimeEventInfoArrayMap;
    LabelNameToTimeEventInfoArrayMap mLabelNameToTimeEventInfoArrayMap;
    TimeEventInfoArray mCurTimeEventInfoArray;
    
    // script handler
    ccScriptFunction m_scriptHandler;
    
public:
    CCSuperAnim();
    virtual ~CCSuperAnim();
    static CCSuperAnim *create(const std::string& theAbsAnimFile, int theId);
    static CCSuperAnim *create(const std::string& theAbsAnimFile, int theId, ccScriptFunction func);
    static CCSuperAnim *create(const std::string& theAbsAnimFile, int theId, CCSuperAnimListener *theListener);

    bool Init(const std::string& theAbsAnimFile, int theId, CCSuperAnimListener *theListener);
    void draw();
    void update(float dt);
    void setFlipX(bool isFlip);
    void setFlipY(bool isFlip);
    bool isFlipX();
    bool isFlipY();

    bool PlaySection(const std::string &theLabel, bool isLoop = false);
    void Pause();
    void Resume();
    bool IsPause();
    bool IsPlaying();
    int GetCurFrame();
    int GetId();
    std::string GetCurSectionName();
    bool HasSection(const std::string &theLabelName);
    void setSpeedFactor(float theNewSpeedFactor);
    
    // for replaceable sprite
    void replaceSprite(const std::string &theOriginSpriteName, const std::string &theNewSpriteName);
    void resumeSprite(const std::string &theOriginSpriteName);
    
    // for time event
    // theTimeFactor is in [0.0f, 1.0f],
    // theTimeFactor = 0.0f means the event will be triggered at the first frame,
    // theTimeFactor = 1.0f means the event will be triggered at the last frame
    void registerTimeEvent(const std::string &theLabel, float theTimeFactor, int theEventId);
    void removeTimeEvent(const std::string &theLabel, int theEventId);
private:
    // support sprite sheet
    void tryLoadSpriteSheet();
    void tryUnloadSpirteSheet();
};

NS_CC_EXT_END

#endif