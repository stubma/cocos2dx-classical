//
//  MacGUIEditorTestScene.h
//  TestCpp
//
//  Created by maruojie on 14/11/28.
//
//

#ifndef __TestCpp__MacGUIEditorTestScene__
#define __TestCpp__MacGUIEditorTestScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../testBasic.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class MacGUIEditorTestMainLayer : public CCLayer
{
public:
    static MacGUIEditorTestMainLayer* create();
    virtual ~MacGUIEditorTestMainLayer();
    virtual bool init();
    void onButtonClicked(UIWidget* sender, TouchEventType e);
};

class MacGUIEditorTestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(CCObject* pSender);
};

#endif /* defined(__TestCpp__MacGUIEditorTestScene__) */
