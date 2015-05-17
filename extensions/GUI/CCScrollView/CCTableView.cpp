/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
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
#include "CCTableView.h"
#include "CCTableViewCell.h"
#include "LuaBasicConversions.h"
#include "CCLuaEngine.h"

NS_CC_EXT_BEGIN

CCTableView* CCTableView::create(CCTableViewDataSource* dataSource, CCSize size)
{
    return CCTableView::create(dataSource, size, NULL);
}

CCTableView* CCTableView::create(CCSize size) {
    return CCTableView::create(NULL, size);
}

CCTableView* CCTableView::create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container)
{
    CCTableView *table = new CCTableView();
    table->initWithViewSize(size, container);
    CC_SAFE_AUTORELEASE(table);
    table->setDataSource(dataSource);
    table->_updateCellPositions();
    table->_updateContentSize();
    
    return table;
}

bool CCTableView::initWithViewSize(CCSize size, CCNode* container/* = NULL*/)
{
    if (CCScrollView::initWithViewSize(size,container))
    {
        m_pCellsUsed = new CCArrayForObjectSorting();
        m_pCellsFreed = new CCArrayForObjectSorting();
        m_pIndices = new std::set<unsigned int>();
        m_colCount = 1;
        setDirection(kCCScrollViewDirectionVertical);
        
        CCScrollView::setDelegate(this);
        return true;
    }
    return false;
}

CCTableView::CCTableView()
: m_pTouchedCell(NULL)
, m_pIndices(NULL)
, m_pCellsUsed(NULL)
, m_pCellsFreed(NULL)
, m_pDataSource(NULL)
, m_pTableViewDelegate(NULL)
, m_viewRows(-1)
, m_rowSpacing(0)
, m_colSpacing(0)
, m_insets(ccInsetsZero)
{
    memset(&m_scriptHandler, 0, sizeof(ccScriptFunction));
}

CCTableView::~CCTableView()
{
    CC_SAFE_DELETE(m_pIndices);
    CC_SAFE_RELEASE(m_pCellsUsed);
    CC_SAFE_RELEASE(m_pCellsFreed);
    unregisterScriptTableViewEventHandler();
}

void CCTableView::reloadData(bool keepOffset)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pCellsUsed, pObj)
    {
        CCTableViewCell* cell = (CCTableViewCell*)pObj;
        
        onTableCellWillRecycle(cell);
        
        m_pCellsFreed->addObject(cell);
        cell->reset();
        if (cell->getParent() == getContainer())
        {
            getContainer()->removeChild(cell, true);
        }
    }
    
    m_pIndices->clear();
    CC_SAFE_RELEASE(m_pCellsUsed);
    m_pCellsUsed = new CCArrayForObjectSorting();
    
    _updateCellPositions();
    _updateContentSize(keepOffset);
    if (onNumberOfCellsInTableView() > 0)
    {
        scrollViewDidScroll(this);
    }
}

CCTableViewCell *CCTableView::cellAtIndex(unsigned int idx)
{
    CCTableViewCell *found = NULL;
    
    if (m_pIndices->find(idx) != m_pIndices->end())
    {
        found = (CCTableViewCell *)m_pCellsUsed->objectWithObjectID(idx);
    }
    
    return found;
}

void CCTableView::updateCellAtIndex(unsigned int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    unsigned int uCountOfItems = onNumberOfCellsInTableView();
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }
    
    CCTableViewCell* cell = cellAtIndex(idx);
    if (cell)
    {
        _moveCellOutOfSight(cell);
    }
    cell = onTableCellAtIndex(idx);
    _setIndexForCell(idx, cell);
    _addCellIfNecessary(cell);
}

void CCTableView::insertCellAtIndex(unsigned  int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    
    unsigned int uCountOfItems = onNumberOfCellsInTableView();
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }
    
    CCTableViewCell* cell = NULL;
    int newIdx = 0;
    
    cell = (CCTableViewCell*)m_pCellsUsed->objectWithObjectID(idx);
    if (cell)
    {
        newIdx = m_pCellsUsed->indexOfSortedObject(cell);
        for (unsigned int i=newIdx; i<m_pCellsUsed->count(); i++)
        {
            cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(i);
            _setIndexForCell(cell->getIdx()+1, cell);
        }
    }
    
    //insert a new cell
    cell = onTableCellAtIndex(idx);
    _setIndexForCell(idx, cell);
    _addCellIfNecessary(cell);
    _updateCellPositions();
    _updateContentSize();
}

void CCTableView::removeCellAtIndex(unsigned int idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    
    unsigned int uCountOfItems = onNumberOfCellsInTableView();
    if (0 == uCountOfItems || idx > uCountOfItems-1)
    {
        return;
    }
    
    unsigned int newIdx = 0;
    
    CCTableViewCell* cell = cellAtIndex(idx);
    if (!cell)
    {
        return;
    }
    
    newIdx = m_pCellsUsed->indexOfSortedObject(cell);
    
    //remove first
    _moveCellOutOfSight(cell);
    
    m_pIndices->erase(idx);

    for (unsigned int i=m_pCellsUsed->count()-1; i > newIdx; i--)
    {
        cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(i);
        _setIndexForCell(cell->getIdx()-1, cell);
    }
}

CCTableViewCell *CCTableView::dequeueCell(const string& name)
{
    CCTableViewCell *cell = NULL;
    
    if (m_pCellsFreed->count() == 0) {
        cell = NULL;
    } else {
        if(name.empty()) {
            cell = (CCTableViewCell*)m_pCellsFreed->objectAtIndex(0);
            CC_SAFE_RETAIN(cell);
            m_pCellsFreed->removeObjectAtIndex(0);
            CC_SAFE_AUTORELEASE(cell);
        } else {
            CCObject* obj;
            CCARRAY_FOREACH(m_pCellsFreed, obj) {
                CCTableViewCell* c = (CCTableViewCell*)obj;
                if(c->getName() == name) {
                    CC_SAFE_RETAIN(c);
                    m_pCellsFreed->removeObject(c);
                    CC_SAFE_AUTORELEASE(c);
                    cell = c;
                    break;
                }
            }
        }
    }
    return cell;
}

void CCTableView::_addCellIfNecessary(CCTableViewCell * cell)
{
    if (cell->getParent() != getContainer())
    {
        getContainer()->addChild(cell);
    }
    m_pCellsUsed->insertSortedObject(cell);
    m_pIndices->insert(cell->getIdx());
}

void CCTableView::_updateCellPositions() {
    int cellsCount = onNumberOfCellsInTableView();
    m_vCellsPositions.clear();
    m_hCellsPositions.clear();
    
    CCSize cellSize;
    float pos;
    CCScrollViewDirection d = getDirection();
    switch(d) {
        case kCCScrollViewDirectionHorizontal:
        {
            // view rows
            pos = m_insets.top;
            bool first = true;
            for (int i = 0; i < cellsCount; i++) {
                cellSize = onTableCellSizeForIndex(i);
                if(!first) {
                    pos += m_rowSpacing;
                }
                first = false;
                pos += cellSize.height;
                if(pos >= m_tViewSize.height) {
                    m_viewRows = i + 1;
                    break;
                }
            }
            
            // v pos
            pos = m_insets.top;
            first = true;
            for (int i = 0; i < m_viewRows; i++) {
                cellSize = onTableCellSizeForIndex(i);
                if(!first) {
                    pos += m_rowSpacing;
                }
                m_vCellsPositions.push_back(pos);
                first = false;
                pos += cellSize.height;
            }
            m_vCellsPositions.push_back(pos);
            
            // h pos
            pos = m_insets.left;
            first = true;
            for (int i = 0; i < cellsCount; i += m_viewRows) {
                cellSize = onTableCellSizeForIndex(i);
                if(!first) {
                    pos += m_colSpacing;
                }
                m_hCellsPositions.push_back(pos);
                first = false;
                pos += cellSize.width;
            }
            m_hCellsPositions.push_back(pos);
            break;
        }
        default:
        {
            // cols and rows
            int cols = m_colCount;
            
            // v pos
            pos = m_insets.top;
            bool first = true;
            for (int i = 0; i < cellsCount; i += cols) {
                cellSize = onTableCellSizeForIndex(i);
                if(!first) {
                    pos += m_rowSpacing;
                }
                m_vCellsPositions.push_back(pos);
                first = false;
                pos += cellSize.height;
            }
            m_vCellsPositions.push_back(pos);
            
            // h pos
            pos = m_insets.left;
            first = true;
            for (int i = 0; i < cols; i++) {
                cellSize = onTableCellSizeForIndex(i);
                if(!first) {
                    pos += m_colSpacing;
                }
                m_hCellsPositions.push_back(pos);
                first = false;
                pos += cellSize.width;
            }
            m_hCellsPositions.push_back(pos);
            break;
        }
    }
}

void CCTableView::_updateContentSize(bool keepOffset) {
    CCSize contentSize;
    contentSize.width = MAX(m_hCellsPositions[m_hCellsPositions.size() - 1] + m_insets.right, m_tViewSize.width);
    contentSize.height = MAX(m_vCellsPositions[m_vCellsPositions.size() - 1] + m_insets.bottom, m_tViewSize.height);
    setContentSize(contentSize);
    
	if (!keepOffset) {
		if (m_eDirection == kCCScrollViewDirectionHorizontal) {
			setContentOffset(ccp(0,0));
		} else {
			setContentOffset(ccp(0,minContainerOffset().y));
		}
    } else {
        CCPoint offset = getContentOffset();
        CCPoint min = minContainerOffset();
        CCPoint max = maxContainerOffset();
        offset.x = clampf(offset.x, min.x, max.x);
        offset.y = clampf(offset.y, min.y, max.y);
        setContentOffset(offset);
    }
}

CCPoint CCTableView::_offsetFromIndex(unsigned int index) {
    const CCSize& contentSize = getContentSize();
    switch (getDirection()) {
        case kCCScrollViewDirectionHorizontal:
        {
            int row = index % m_viewRows;
            int col = index / m_viewRows;
            return ccp(m_hCellsPositions[col],
                       contentSize.height - m_vCellsPositions[row + 1] + ((row < m_viewRows - 1) ? m_rowSpacing : 0) + 1);
        }
        default:
        {
            int row = index / m_colCount;
            int col = index % m_colCount;
            return ccp(m_hCellsPositions[col],
                       contentSize.height - m_vCellsPositions[row + 1] + ((row < m_vCellsPositions.size() - 2) ? m_rowSpacing : 0) + 1);
        }
    }
}

CCPoint CCTableView::containerOffsetFromIndex(unsigned int index) {
    // get col of cell
    int col;
    switch (getDirection()) {
        case kCCScrollViewDirectionHorizontal:
            col = index / m_viewRows;
            break;
        default:
            col = index % m_colCount;
            break;
    }
    
    // offset in container, view size, cell width
    CCPoint offset = _offsetFromIndex(index);
    CCSize viewSize = getViewSize();
    float cellWidth = m_hCellsPositions[col + 1] - m_hCellsPositions[col];

    // calculate
    return ccp(MIN(viewSize.width - offset.x - cellWidth, 0),
               MIN(viewSize.height - offset.y, 0));
}

int CCTableView::_indexFromOffset(CCPoint offset, bool excludeMargin) {
    // max index
    const int maxIdx = onNumberOfCellsInTableView() - 1;
    
    // locate
    const CCSize& contentSize = getContentSize();
    offset.y = contentSize.height - offset.y;
    int c = (int)m_hCellsPositions.size();
    int row, col = c;
    for(int i = 0; i < c; i++) {
        if(offset.x < m_hCellsPositions[i]) {
            col = MAX(0, i - 1);
            break;
        } else if(offset.x == m_hCellsPositions[i]) {
            col = MAX(0, i);
            break;
        }
    }
    c = (int)m_vCellsPositions.size();
    row = c;
    for(int i = 0; i < c; i++) {
        if(offset.y < m_vCellsPositions[i]) {
            row = MAX(0, i - 1);
            break;
        } else if(offset.y == m_vCellsPositions[i]) {
            row = MAX(0, i);
            break;
        }
    }
    
    // index
    int index = -1;
    
    // margin, space checking
    if(excludeMargin) {
        if(row == 0 && offset.y < m_insets.top) {
            return index;
        }
        if(row < m_vCellsPositions.size() - 2 && offset.y > m_vCellsPositions[row + 1] - m_rowSpacing) {
            return index;
        }
        if(col == 0 && offset.x < m_insets.left) {
            return index;
        }
        if(col < m_hCellsPositions.size() - 2 && offset.x > m_hCellsPositions[col + 1] - m_colSpacing) {
            return index;
        }
    }
    
    // get index, without range limit
    switch (getDirection()) {
        case kCCScrollViewDirectionHorizontal:
            index = row + m_viewRows * col;
            break;
        default:
            index = col + row * m_colCount;
            break;
    }
    
    // range checking
    index = MAX(0, index);
    if(index > maxIdx) {
        index = CC_INVALID_INDEX;
    }
    
    return index;
}

void CCTableView::_moveCellOutOfSight(CCTableViewCell *cell)
{
    onTableCellWillRecycle(cell);
    
    m_pCellsFreed->addObject(cell);
    m_pCellsUsed->removeSortedObject(cell);
    m_pIndices->erase(cell->getIdx());
    // [m_pIndices removeIndex:cell.idx];
    cell->reset();
    if (cell->getParent() == getContainer()) {
        getContainer()->removeChild(cell, true);;
    }
}

void CCTableView::_setIndexForCell(unsigned int index, CCTableViewCell *cell)
{
    cell->setAnchorPoint(ccp(0.0f, 0.0f));
    cell->setPosition(_offsetFromIndex(index));
    cell->setIdx(index);
}

void CCTableView::scrollViewDidScroll(CCScrollView* view)
{
    unsigned int uCountOfItems = onNumberOfCellsInTableView();
    if (0 == uCountOfItems)
    {
        return;
    }
    
    if(m_pTableViewDelegate != NULL) {
        m_pTableViewDelegate->scrollViewDidScroll(this);
    }
    
    unsigned int startIdx = 0, endIdx = 0, idx = 0, maxIdx = 0;
    CCPoint offset = ccpMult(getContentOffset(), -1);
    maxIdx = MAX(uCountOfItems-1, 0);
    
    offset.y = offset.y + m_tViewSize.height/getContainer()->getScaleY();
    startIdx = _indexFromOffset(offset);
	if (startIdx == CC_INVALID_INDEX)
	{
		startIdx = uCountOfItems - 1;
	}
    
    offset.y -= m_tViewSize.height/getContainer()->getScaleY();
    offset.x += m_tViewSize.width/getContainer()->getScaleX();
    
    endIdx   = _indexFromOffset(offset);
    if (endIdx == CC_INVALID_INDEX)
	{
		endIdx = uCountOfItems - 1;
	}
    
#if 0 // For Testing.
    CCObject* pObj;
    int i = 0;
    CCARRAY_FOREACH(m_pCellsUsed, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells Used index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("---------------------------------------");
    i = 0;
    CCARRAY_FOREACH(m_pCellsFreed, pObj)
    {
        CCTableViewCell* pCell = (CCTableViewCell*)pObj;
        CCLog("cells freed index %d, value = %d", i, pCell->getIdx());
        i++;
    }
    CCLog("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
#endif
    
    if (m_pCellsUsed->count() > 0)
    {
        CCTableViewCell* cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(0);
        
        idx = cell->getIdx();
        while(idx <startIdx)
        {
            _moveCellOutOfSight(cell);
            if (m_pCellsUsed->count() > 0)
            {
                cell = (CCTableViewCell*)m_pCellsUsed->objectAtIndex(0);
                idx = cell->getIdx();
            }
            else
            {
                break;
            }
        }
    }
    if (m_pCellsUsed->count() > 0)
    {
        CCTableViewCell *cell = (CCTableViewCell*)m_pCellsUsed->lastObject();
        idx = cell->getIdx();
        
        while(idx <= maxIdx && idx > endIdx)
        {
            _moveCellOutOfSight(cell);
            if (m_pCellsUsed->count() > 0)
            {
                cell = (CCTableViewCell*)m_pCellsUsed->lastObject();
                idx = cell->getIdx();
                
            }
            else
            {
                break;
            }
        }
    }
    
    for (unsigned int i=startIdx; i <= endIdx; i++)
    {
        //if ([m_pIndices containsIndex:i])
        if (m_pIndices->find(i) != m_pIndices->end())
        {
            continue;
        }
        updateCellAtIndex(i);
    }
}

void CCTableView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isVisible()) {
        return;
    }
    
    if (m_pTouchedCell){
		CCRect bb = boundingBox();
		bb.origin = m_pParent->convertToWorldSpace(bb.origin);
        
		if (bb.containsPoint(pTouch->getLocation()))
        {
            // save touch point
            CCPoint loc = convertTouchToNodeSpace(pTouch);
            m_tTouchPoint = loc;
            
            // event
            onTableCellUnhighlight();
            onTableCellTouched();
        }
        
        m_pTouchedCell = NULL;
    }
    
    CCScrollView::ccTouchEnded(pTouch, pEvent);
}

bool CCTableView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isVisible()) {
        return false;
    }
    
    bool touchResult = CCScrollView::ccTouchBegan(pTouch, pEvent);
    
    if(m_pTouches->count() == 1) {
        unsigned int        index;
        CCPoint           point;
        
        point = getContainer()->convertTouchToNodeSpace(pTouch);
        
        index = _indexFromOffset(point, true);
		if (index == CC_INVALID_INDEX)
		{
			m_pTouchedCell = NULL;
		}
        else
		{
			m_pTouchedCell  = cellAtIndex(index);
		}
        
        if (m_pTouchedCell) {
            onTableCellHighlight();
        }
    }
    else if(m_pTouchedCell) {
        onTableCellUnhighlight();
        m_pTouchedCell = NULL;
    }
    
    return touchResult;
}

void CCTableView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchMoved(pTouch, pEvent);
    
    if (m_pTouchedCell && isTouchMoved()) {
        onTableCellUnhighlight();
        m_pTouchedCell = NULL;
    }
}

void CCTableView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCScrollView::ccTouchCancelled(pTouch, pEvent);
    
    if (m_pTouchedCell) {
        onTableCellUnhighlight();
        m_pTouchedCell = NULL;
    }
}

void CCTableView::onTableCellHighlight() {
    if(m_pTableViewDelegate) {
        m_pTableViewDelegate->tableCellHighlight(this, m_pTouchedCell);
    }
    
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("highlight"));
        pArrayArgs->addObject(m_pTouchedCell);
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

void CCTableView::onTableCellUnhighlight() {
    if(m_pTableViewDelegate) {
        m_pTableViewDelegate->tableCellUnhighlight(this, m_pTouchedCell);
    }
    
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("unhighlight"));
        pArrayArgs->addObject(m_pTouchedCell);
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

void CCTableView::onTableCellTouched() {
    if(m_pTableViewDelegate) {
        m_pTableViewDelegate->tableCellTouched(this, m_pTouchedCell);
    }
    
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("touched"));
        pArrayArgs->addObject(m_pTouchedCell);
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

void CCTableView::onTableCellWillRecycle(CCTableViewCell* cell) {
    if(m_pTableViewDelegate) {
        m_pTableViewDelegate->tableCellWillRecycle(this, cell);
    }
    
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("recycle"));
        pArrayArgs->addObject(cell);
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

unsigned int CCTableView::onNumberOfCellsInTableView() {
    if(m_pDataSource) {
        return m_pDataSource->numberOfCellsInTableView(this);
    } else if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(2);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("num"));
        return CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    } else {
        return 0;
    }
}

CCSize CCTableView::onTableCellSizeForIndex(unsigned int idx) {
    if(m_pDataSource) {
        return m_pDataSource->tableCellSizeForIndex(this, idx);
    } else if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("size"));
        pArrayArgs->addObject(CCInteger::create(idx));
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs, this, valuecollector_selector(CCTableView::collectReturnedCCSize));
        return m_scriptRetSize;
    } else {
        return CCSizeZero;
    }
}

CCTableViewCell* CCTableView::onTableCellAtIndex(unsigned int idx) {
    if(m_pDataSource) {
        return m_pDataSource->tableCellAtIndex(this, idx);
    } else if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(3);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("cell"));
        pArrayArgs->addObject(CCInteger::create(idx));
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs, this, valuecollector_selector(CCTableView::collectReturnedCell));
        return m_scriptRetCell;
    } else {
        return NULL;
    }
}

void CCTableView::collectReturnedCCSize() {
    CCLuaEngine* engine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
    lua_State* L = engine->getLuaStack()->getLuaState();
    CCSize size;
    if(!luaval_to_size(L, -1, &m_scriptRetSize)) {
        m_scriptRetSize = CCSizeZero;
    }
}

void CCTableView::collectReturnedCell() {
    CCLuaEngine* engine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
    lua_State* L = engine->getLuaStack()->getLuaState();
    if(!luaval_to_object<CCTableViewCell>(L, -1, "CCTableViewCell", &m_scriptRetCell)) {
        m_scriptRetCell = NULL;
    }
}

void CCTableView::registerScriptTableViewEventHandler(ccScriptFunction func) {
    unregisterScriptTableViewEventHandler();
    m_scriptHandler = func;
}

void CCTableView::unregisterScriptTableViewEventHandler() {
    if(m_scriptHandler.handler) {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_scriptHandler.handler);
        m_scriptHandler.handler = 0;
    }
}

void CCTableView::setColCount(unsigned int cols) {
    m_colCount = cols;
    _updateCellPositions();
    _updateContentSize();
}

void CCTableView::setInsets(ccInsets var) {
    m_insets = var;
    _updateCellPositions();
    _updateContentSize();
}

void CCTableView::setRowSpacing(float var) {
    m_rowSpacing = var;
    _updateCellPositions();
    _updateContentSize();
}

void CCTableView::setColSpacing(float var) {
    m_colSpacing = var;
    _updateCellPositions();
    _updateContentSize();
}

int CCTableView::getRealRows() {
    return (int)m_vCellsPositions.size() - 1;
}

NS_CC_EXT_END