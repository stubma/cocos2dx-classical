/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
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

#ifndef __UIPAGEVIEW_H__
#define __UIPAGEVIEW_H__

#include "../../Layouts/Layout.h"
#include "UIScrollInterface.h"

using namespace std;

NS_CC_BEGIN

class CCVelocityTracker;

namespace ui {

typedef enum
{
    PAGEVIEW_EVENT_TURNING,
}PageViewEventType;

typedef void (CCObject::*SEL_PageViewEvent)(CCObject*, PageViewEventType);
#define pagevieweventselector(_SELECTOR)(SEL_PageViewEvent)(&_SELECTOR)

typedef enum {
    PAGEVIEW_TOUCHLEFT,
    PAGEVIEW_TOUCHRIGHT
}PVTouchDir;
    
class PageView;
    
class PageViewDataSource {
public:
    virtual int pageViewItemCount(PageView* pv) = 0;
    virtual Widget* pageItemAtIndex(PageView* pv, int index) = 0;
    virtual void pageItemDidRecycled(PageView* pv, Widget* item) = 0;
};

class PageView : public Layout , public UIScrollInterface
{
    DECLARE_CLASS_GUI_INFO
    
private:
    CCVelocityTracker* m_tracker;
    CCDictionary m_cycledPages;
    Widget* m_dstPage;
    int m_dstIndex;
    
public:
    /**
     * Default constructor
     */
    PageView();
    
    /**
     * Default destructor
     */
    virtual ~PageView();
    
    /**
     * Allocates and initializes.
     */
    static PageView* create();
    
    // reload, and set current page index to specified one
    void reloadData(int wantedPageIndex);
    void reloadData();
    
    // reuse item
    void enqueuePageItem(Widget* item, const string& itemId);
    Widget* dequeuePageItem(const string& itemId);
    void recyclePage(Widget* page);
    
    /**
     * scroll pageview to index.
     *
     * @param idx    index of page.
     */
    void scrollToPage(int idx, bool animation = true);
    
    /**
     * Gets current page index.
     *
     * @return current page index.
     */
    int getCurPageIndex() const;
    
    // event
    void addEventListenerPageView(CCObject *target, SEL_PageViewEvent selector);

    virtual bool onTouchBegan(CCTouch *touch, CCEvent *unusedEvent);
    virtual void onTouchMoved(CCTouch *touch, CCEvent *unusedEvent);
    virtual void onTouchEnded(CCTouch *touch, CCEvent *unusedEvent);
    virtual void onTouchCancelled(CCTouch *touch, CCEvent *unusedEvent);
    
    // override "update" method of widget.
    virtual void update(float dt);
    
    /**
     * Sets LayoutType.
     *
     * @see LayoutType
     *
     * @param LayoutType
     */
    virtual void setLayoutType(LayoutType type) {}
    
    /**
     * Gets LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    virtual LayoutType getLayoutType() const { return LAYOUT_ABSOLUTE; }
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const;

    virtual void onEnter();
    
protected:
    /**
     * Push back a page to pageview.
     *
     * @param page    page to be added to pageview.
     */
    void addPage(Widget* page, int index);
    
    virtual bool init();
    float getPositionXByIndex(int idx);
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void handleMoveLogic(const CCPoint &touchPoint);
    virtual void handleReleaseLogic(const CCPoint &touchPoint);
    virtual void interceptTouchEvent(int handleState, Widget* sender, const CCPoint &touchPoint);
    virtual void checkChildInfo(int handleState, Widget* sender, const CCPoint &touchPoint);
    void movePages(float offset);
    void movePage(Widget* page, float offset);
    void pageTurningEvent();
    void updateChildrenSize();
    virtual void onSizeChanged();
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    virtual void doLayout() {if (!_doLayoutDirty){return;} _doLayoutDirty = false;};
    
protected:
    int _curPageIdx;
    PVTouchDir _touchMoveDir;
    float _touchStartLocation;
    float _touchMoveStartLocation;
    CCPoint _movePagePoint;
    float _leftBoundary;
    float _rightBoundary;
    bool _isAutoScrolling;
    float _autoScrollDistance;
    float _autoScrollSpeed;
    int _autoScrollDir;
    float _childFocusCancelOffset;
    CCObject* _pageViewEventListener;
    SEL_PageViewEvent _pageViewEventSelector;

    CC_SYNTHESIZE(PageViewDataSource*, m_dataSource, DataSource);
    CC_SYNTHESIZE(Widget*, _leftChild, LeftChild);
    CC_SYNTHESIZE(Widget*, _rightChild, RightChild);
    CC_SYNTHESIZE(Widget*, m_curPage, CurPage);
};

}
NS_CC_END

#endif /* defined(__PageView__) */
