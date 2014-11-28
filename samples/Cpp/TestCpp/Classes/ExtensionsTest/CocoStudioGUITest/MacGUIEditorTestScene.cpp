//
//  MacGUIEditorTestScene.cpp
//  TestCpp
//
//  Created by maruojie on 14/11/28.
//
//

#include "MacGUIEditorTestScene.h"
#include "cocos-ext.h"
#include "CocoStudioGUITest.h"

using namespace cocos2d::ui;

MacGUIEditorTestMainLayer* MacGUIEditorTestMainLayer::create() {
    MacGUIEditorTestMainLayer* l = new MacGUIEditorTestMainLayer();
    if(l->init()) {
        l->autorelease();
        return l;
    }
    CC_SAFE_RELEASE(l);
    return NULL;
}

MacGUIEditorTestMainLayer::~MacGUIEditorTestMainLayer() {
}

bool MacGUIEditorTestMainLayer::init() {
    if(!CCLayer::init())
        return false;
    
    UIWidget* widget = GUIReader::shareReader()->widgetFromJsonFile("cocosui/mac/mac_cocostudio_test_1_1.json");
    TouchGroup* tg = TouchGroup::create();
    addChild(tg);
    tg->addWidget(widget);
    
    UIWidget* btn = UIHelper::seekWidgetByName(widget, "btn");
    btn->addTouchEventListener(this, toucheventselector(MacGUIEditorTestMainLayer::onButtonClicked));
    
    return true;
}

void MacGUIEditorTestMainLayer::onButtonClicked(UIWidget* sender, TouchEventType e) {
    CCLOG("button clicked");
}

void MacGUIEditorTestScene::onEnter()
{
    CCScene::onEnter();
    
    CCLabelTTF* label = CCLabelTTF::create("Back", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(MacGUIEditorTestScene::BackCallback));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void MacGUIEditorTestScene::runThisTest()
{
    CCLayer* pLayer = MacGUIEditorTestMainLayer::create();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void MacGUIEditorTestScene::BackCallback(CCObject* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}