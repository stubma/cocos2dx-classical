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

#include "PageView.h"
#include "support/ui/CCVelocityTracker.h"
#include "LuaBasicConversions.h"
#include "CCLuaEngine.h"

NS_CC_UI_BEGIN

IMPLEMENT_CLASS_GUI_INFO(PageView)
    
PageView::PageView():
_curPageIdx(0),
m_tracker(NULL),
m_dataSource(NULL),
m_curPage(NULL),
m_dstPage(NULL),
_touchMoveDir(PAGEVIEW_TOUCHLEFT),
_touchStartLocation(0.0f),
_touchMoveStartLocation(0.0f),
_movePagePoint(CCPointZero),
m_leftChild(NULL),
m_rightChild(NULL),
_leftBoundary(0.0f),
_rightBoundary(0.0f),
_isAutoScrolling(false),
_autoScrollDistance(0.0f),
_autoScrollSpeed(0.0f),
_autoScrollDir(0),
_childFocusCancelOffset(5.0f),
_pageViewEventListener(NULL),
_pageViewEventSelector(NULL)
{
    memset(&m_scriptHandler, 0, sizeof(ccScriptFunction));
}

PageView::~PageView()
{
    // release others
    unregisterScriptPageViewEventHandler();
    CC_SAFE_RELEASE(m_tracker);
    _pageViewEventListener = NULL;
    _pageViewEventSelector = NULL;
}

PageView* PageView::create()
{
    PageView* widget = new PageView();
    if (widget && widget->init())
    {
        CC_SAFE_AUTORELEASE(widget);
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}
    
void PageView::onEnter()
{
    Layout::onEnter();
    scheduleUpdate();
}

bool PageView::init()
{
    if (Layout::init())
    {
        setClippingEnabled(true);
        setTouchEnabled(true);
        return true;
    }
    return false;
}
    
void PageView::recyclePage(Widget* page) {
    if(page) {
        enqueuePageItem(page, page->getName());
        page->removeFromParent();
        onPageViewEventPageDidRecycled(page);
        page = NULL;
    }
}
    
void PageView::reloadData() {
    // recycle pages
    recyclePage(m_curPage);
    if(m_dstPage != m_rightChild && m_dstPage != m_leftChild && m_dstPage != m_curPage)
        recyclePage(m_dstPage);
    recyclePage(m_leftChild);
    recyclePage(m_rightChild);
    m_curPage = NULL;
    m_leftChild = NULL;
    m_rightChild = NULL;
    m_dstPage = NULL;
    
    // recreate current page
    if(m_dataSource || m_scriptHandler.handler) {
        m_curPage = onPageViewEventPageAtIndex(_curPageIdx);
        addPage(m_curPage, 0);
        if(_curPageIdx > 0) {
            m_leftChild = onPageViewEventPageAtIndex(_curPageIdx - 1);
            addPage(m_leftChild, -1);
        }
        if(_curPageIdx < onPageViewEventPageCount() - 1) {
            m_rightChild = onPageViewEventPageAtIndex(_curPageIdx + 1);
            addPage(m_rightChild, 1);
        }
    }
    
    // trigger a page turn event for every reload
    m_dstIndex = _curPageIdx;
    m_dstPage = m_curPage;
    pageTurningEvent();
}
    
void PageView::reloadData(int wantedPageIndex) {
    _curPageIdx = wantedPageIndex;
    reloadData();
}

void PageView::addPage(Widget* page, int index)
{
    if (!page)
    {
        return;
    }
    if (page->getWidgetType() != WidgetTypeContainer)
    {
        return;
    }
    CCSize pSize = page->getSize();
    CCSize pvSize = getSize();
    if (!pSize.equals(pvSize))
    {
        CCLOG("page size does not match pageview size, it will be force sized!");
        page->setSize(pvSize);
    }
    page->setPosition(CCPoint(getPositionXByIndex(index), 0));
    addChild(page);
}

float PageView::getPositionXByIndex(int idx) {
    float cx = m_curPage ? m_curPage->getPositionX() : 0;
    return cx + getSize().width * idx;
}

void PageView::onSizeChanged()
{
    Layout::onSizeChanged();
    _rightBoundary = getSize().width;
    updateChildrenSize();
}

void PageView::updateChildrenSize()
{
    CCSize selfSize = getSize();
    if(m_curPage)
        m_curPage->setSize(selfSize);
    if(m_leftChild)
        m_leftChild->setSize(selfSize);
    if(m_rightChild)
        m_rightChild->setSize(selfSize);
}

void PageView::scrollToPage(int idx, bool animation)
{
    // index validating
    int count = onPageViewEventPageCount();
    if (idx < 0 || idx >= count) {
        return;
    }
    
    // if in auto scrolling, immediately finish it
    if(_isAutoScrolling) {
        update(1);
    }
    
    // calculate distance
    m_dstIndex = idx;
    int delta = idx - _curPageIdx;
    _autoScrollDistance = -MIN(MAX(delta, -2), 2) * getSize().width;
    _autoScrollDistance -= m_curPage->getPositionX();
    
    // create page if needed
    if(abs(delta) > 1) {
        Widget* page = onPageViewEventPageAtIndex(idx);
        addPage(page, MIN(MAX(delta, -2), 2));
        m_dstPage = page;
    } else if(abs(delta) > 0) {
        m_dstPage = delta > 0 ? m_rightChild : m_leftChild;
    } else {
        m_dstPage = m_curPage;
    }
    
    // scroll
    if(animation) {
        _autoScrollSpeed = fabs(_autoScrollDistance) / 0.2f;
        _autoScrollDir = _autoScrollDistance > 0 ? 1 : 0;
        _isAutoScrolling = true;
    } else {
        movePages(_autoScrollDistance);
        pageTurningEvent();
    }
}

void PageView::update(float dt) {
    if (_isAutoScrolling) {
        switch (_autoScrollDir) {
            case 0:
            {
                float step = _autoScrollSpeed * dt;
                if (_autoScrollDistance + step >= 0.0f) {
                    step = -_autoScrollDistance;
                    _autoScrollDistance = 0.0f;
                    _isAutoScrolling = false;
                } else {
                    _autoScrollDistance += step;
                }
                movePages(-step);
                if (!_isAutoScrolling) {
                    pageTurningEvent();
                }
                break;
            }
            case 1:
            {
                float step = _autoScrollSpeed * dt;
                if (_autoScrollDistance - step <= 0.0f) {
                    step = _autoScrollDistance;
                    _autoScrollDistance = 0.0f;
                    _isAutoScrolling = false;
                } else {
                    _autoScrollDistance -= step;
                }
                movePages(step);
                if (!_isAutoScrolling) {
                    pageTurningEvent();
                }
                break;
            }
            default:
                break;
        }
    }
}

bool PageView::onTouchBegan(CCTouch *touch, CCEvent *unusedEvent) {
    // don't handle touch when scrolling
    if(_isAutoScrolling)
        return false;
    
    // add touch began to tracker
    if(!m_tracker) {
        m_tracker = CCVelocityTracker::create();
        CC_SAFE_RETAIN(m_tracker);
    }
    m_tracker->addTouchBegan(touch);
    
    bool pass = Layout::onTouchBegan(touch, unusedEvent);
    if (_hitted) {
        handlePressLogic(touch->getLocation());
    }
    return pass;
}

void PageView::onTouchMoved(CCTouch *touch, CCEvent *unusedEvent) {
    // add touch move to tracker
    if(m_tracker) {
        m_tracker->addTouchMoved(touch);
    }
    
    _touchMovePos = touch->getLocation();
    handleMoveLogic(_touchMovePos);
    Widget* widgetParent = getWidgetParent();
    if (widgetParent) {
        widgetParent->checkChildInfo(1,this,_touchMovePos);
    }
    moveEvent();
}

void PageView::onTouchEnded(CCTouch *touch, CCEvent *unusedEvent) {
    Layout::onTouchEnded(touch, unusedEvent);
    handleReleaseLogic(_touchEndPos);
}
    
void PageView::onTouchCancelled(CCTouch *touch, CCEvent *unusedEvent) {
    Layout::onTouchCancelled(touch, unusedEvent);
    handleReleaseLogic(touch->getLocation());
}
    
void PageView::movePage(Widget* page, float offset) {
    if(page) {
        CCPoint p = page->getPosition();
        p.x += offset;
        page->setPosition(p);
    }
}

void PageView::movePages(float offset) {
    movePage(m_curPage, offset);
    movePage(m_leftChild, offset);
    movePage(m_rightChild, offset);
    if(m_dstPage != m_leftChild && m_dstPage != m_rightChild && m_dstPage != m_curPage)
        movePage(m_dstPage, offset);
}

void PageView::handlePressLogic(const CCPoint &touchPoint) {
    CCPoint nsp = convertToNodeSpace(touchPoint);
    _touchMoveStartLocation = nsp.x;
    _touchStartLocation = nsp.x;
}

void PageView::handleMoveLogic(const CCPoint &touchPoint) {
    CCPoint nsp = convertToNodeSpace(touchPoint);
    float offset = 0.0;
    float moveX = nsp.x;
    offset = moveX - _touchMoveStartLocation;
    _touchMoveStartLocation = moveX;
    if (offset < 0) {
        _touchMoveDir = PAGEVIEW_TOUCHLEFT;
    } else if (offset > 0) {
        _touchMoveDir = PAGEVIEW_TOUCHRIGHT;
    }
    movePages(offset);
}

void PageView::handleReleaseLogic(const CCPoint &touchPoint) {
    // get velocity
    float xVelocity = 0;
    if (m_tracker) {
        m_tracker->computeCurrentVelocity(1000);
        xVelocity = m_tracker->getXVelocity();
        CC_SAFE_RELEASE_NULL(m_tracker);
    }
    
    // scroll to other page or back to current page
    CCPoint curPagePos = m_curPage ? m_curPage->getPosition() : CCPointZero;
    int pageCount = onPageViewEventPageCount();
    float curPageLocation = curPagePos.x;
    float pageWidth = getSize().width;
    float boundary = pageWidth / 8.0f;
    if (xVelocity <= -500.0f || curPageLocation <= -boundary) {
        if (_curPageIdx >= pageCount - 1) {
            movePages(-curPageLocation);
        } else {
            scrollToPage(_curPageIdx + 1);
        }
    } else if (xVelocity >= 500.0f || curPageLocation >= boundary) {
        if (_curPageIdx <= 0) {
            movePages(-curPageLocation);
        } else {
            scrollToPage(_curPageIdx - 1);
        }
    } else {
        scrollToPage(_curPageIdx);
    }
}

void PageView::checkChildInfo(int handleState,Widget* sender, const CCPoint &touchPoint) {
    if(isEnabled() && isTouchEnabled()) {
        interceptTouchEvent(handleState, sender, touchPoint);
    }
}

void PageView::interceptTouchEvent(int handleState, Widget *sender, const CCPoint &touchPoint) {
    if(_isAutoScrolling)
        return;
    
    switch (handleState) {
        case 0:
            // add touch began to tracker
            if(!m_tracker) {
                m_tracker = CCVelocityTracker::create();
                CC_SAFE_RETAIN(m_tracker);
            }
            m_tracker->addTouchBegan(touchPoint);
            
            handlePressLogic(touchPoint);
            break;
        case 1:
        {
            // add touch move to tracker
            if(m_tracker) {
                m_tracker->addTouchMoved(touchPoint);
            }
            
            float offset = 0;
            offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
            if (offset > _childFocusCancelOffset)
            {
                sender->setFocused(false);
                handleMoveLogic(touchPoint);
            }
            
            break;
        }
        case 2:
            handleReleaseLogic(touchPoint);
            break;
        case 3:
            handleReleaseLogic(touchPoint);
            break;
    }
}

void PageView::pageTurningEvent() {
    // clear flag and dest page
    if(m_dstPage == m_leftChild) {
        recyclePage(m_rightChild);
        m_rightChild = m_curPage;
        m_curPage = m_leftChild;
        m_leftChild = m_dstIndex > 0 ? onPageViewEventPageAtIndex(m_dstIndex - 1) : NULL;
        if(m_leftChild)
            addPage(m_leftChild, -1);
    } else if(m_dstPage == m_rightChild) {
        recyclePage(m_leftChild);
        m_leftChild = m_curPage;
        m_curPage = m_rightChild;
        m_rightChild = (m_dstIndex < onPageViewEventPageCount() - 1) ? onPageViewEventPageAtIndex(m_dstIndex + 1) : NULL;
        if(m_rightChild)
            addPage(m_rightChild, 1);
    } else if(m_dstPage != m_curPage) {
        int delta = m_dstIndex - _curPageIdx;
        if(delta == 2) {
            recyclePage(m_leftChild);
            recyclePage(m_curPage);
            m_leftChild = m_rightChild;
            m_curPage = m_dstPage;
            m_rightChild = (m_dstIndex < onPageViewEventPageCount() - 1) ? onPageViewEventPageAtIndex(m_dstIndex + 1) : NULL;
            if(m_rightChild)
                addPage(m_rightChild, 1);
        } else if(delta == -2) {
            recyclePage(m_rightChild);
            recyclePage(m_curPage);
            m_rightChild = m_leftChild;
            m_curPage = m_dstPage;
            m_leftChild = m_dstIndex > 0 ? onPageViewEventPageAtIndex(m_dstIndex - 1) : NULL;
            if(m_leftChild)
                addPage(m_leftChild, -1);
        } else {
            recyclePage(m_leftChild);
            recyclePage(m_curPage);
            recyclePage(m_rightChild);
            m_curPage = m_dstPage;
            m_leftChild = m_dstIndex > 0 ? onPageViewEventPageAtIndex(m_dstIndex - 1) : NULL;
            if(m_leftChild)
                addPage(m_leftChild, -1);
            m_rightChild = (m_dstIndex < onPageViewEventPageCount() - 1) ? onPageViewEventPageAtIndex(m_dstIndex + 1) : NULL;
            if(m_rightChild)
                addPage(m_rightChild, 1);
        }
    }
    _isAutoScrolling = false;
    _curPageIdx = m_dstIndex;
    m_dstPage = NULL;
    
    // notify event
    onPageViewEventTurning();
}

void PageView::addEventListenerPageView(CCObject *target, SEL_PageViewEvent selector)
{
    _pageViewEventListener = target;
    _pageViewEventSelector = selector;
}

int PageView::getCurPageIndex() const
{
    return _curPageIdx;
}

std::string PageView::getDescription() const
{
    return "PageView";
}

Widget* PageView::createCloneInstance()
{
    return PageView::create();
}

void PageView::copyClonedWidgetChildren(Widget* model)
{
    PageView* pv = dynamic_cast<PageView*>(model);
    if(pv) {
        if(pv->getCurPage()) {
            addPage(pv->getCurPage()->clone(), 0);
        }
        if(pv->getLeftChild()) {
            addPage(pv->getLeftChild()->clone(), -1);
        }
        if(pv->getRightChild()) {
            addPage(pv->getRightChild()->clone(), 1);
        }
    }
}

void PageView::copySpecialProperties(Widget *widget)
{
    PageView* pageView = dynamic_cast<PageView*>(widget);
    if (pageView)
    {
        Layout::copySpecialProperties(widget);
    }
}

void PageView::enqueuePageItem(Widget* item, const string& itemId) {
    CCArray* items = (CCArray*)m_cycledPages.objectForKey(itemId);
    if(!items) {
        items = CCArray::create();
        m_cycledPages.setObject(items, itemId);
    }
    items->addObject(item);
}

Widget* PageView::dequeuePageItem(const string& itemId) {
    CCArray* items = (CCArray*)m_cycledPages.objectForKey(itemId);
    if(items) {
        if(items->count() > 0) {
            Layout* item = (Layout*)items->lastObject();
            CC_SAFE_RETAIN(item);
            items->removeLastObject();
            item->setPosition(CCPointZero);
            item->setScale(1);
            item->setOpacity(255);
            item->setRotation(0);
            CC_SAFE_AUTORELEASE(item);
            return item;
        }
    }
    
    return NULL;
}
 
void PageView::registerScriptPageViewEventHandler(ccScriptFunction func) {
    unregisterScriptPageViewEventHandler();
    m_scriptHandler = func;
}

void PageView::unregisterScriptPageViewEventHandler() {
    if(m_scriptHandler.handler) {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_scriptHandler.handler);
        m_scriptHandler.handler = 0;
    }
}

void PageView::onPageViewEventTurning() {
    if (_pageViewEventListener && _pageViewEventSelector) {
        (_pageViewEventListener->*_pageViewEventSelector)(this, PAGEVIEW_EVENT_TURNING);
    }
    
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(2);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("turning"));
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

int PageView::onPageViewEventPageCount() {
    if(m_dataSource) {
        return m_dataSource->pageViewItemCount(this);
    } else if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(2);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("count"));
        return CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    } else {
        return 0;
    }
}

Widget* PageView::onPageViewEventPageAtIndex(int idx) {
    if(m_dataSource) {
        return m_dataSource->pageItemAtIndex(this, idx);
    } else if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("page"));
        pArrayArgs->addObject(CCInteger::create(idx));
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs, this, valuecollector_selector(PageView::collectReturnedPage));
        return m_scriptRetPage;
    } else {
        return NULL;
    }
}

void PageView::onPageViewEventPageDidRecycled(Widget* page) {
    if(m_dataSource) {
        m_dataSource->pageItemDidRecycled(this, page);
    }
    
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("recycled"));
        pArrayArgs->addObject(page);
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

void PageView::collectReturnedPage() {
    CCLuaEngine* engine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
    lua_State* L = engine->getLuaStack()->getLuaState();
    if(!luaval_to_object<Widget>(L, -1, "Widget", &m_scriptRetPage)) {
        m_scriptRetPage = NULL;
    }
}

NS_CC_UI_END