

#include "UIPageViewTest.h"


// UIPageViewTest
UIPageViewTest::UIPageViewTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UIPageViewTest::~UIPageViewTest()
{
}

bool UIPageViewTest::init()
{
    if (UIScene::init())
    {
        
        return true;
    }
    return false;
}

void UIPageViewTest::pageViewEvent(CCObject *pSender, PageViewEventType type)
{
    switch (type)
    {
        case PAGEVIEW_EVENT_TURNING:
        {
            UIPageView* pageView = dynamic_cast<UIPageView*>(pSender);
            
            m_pDisplayValueLabel->setText(CCString::createWithFormat("page = %d", pageView->getCurPageIndex() + 1)->getCString());
        }
            break;
            
        default:
            break;
    }
}