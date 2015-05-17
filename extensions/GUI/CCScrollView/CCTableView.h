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
#ifndef __CCTableView__
#define __CCTableView__

#include "CCScrollView.h"
#include "CCTableViewCell.h"
#include "CCSorting.h"
#include <set>
#include <vector>
#include "ccMacros.h"

using namespace std;

NS_CC_EXT_BEGIN

class CCTableView;

/**
 * Sole purpose of this delegate is to single touch event in this version.
 * @js NA
 * @lua NA
 */
class CC_DLL CCTableViewDelegate : public CCScrollViewDelegate
{
public:
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     */
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) = 0;
    
    /**
     * Delegate to respond a table cell press event.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell){};
    
    /**
     * Delegate to respond a table cell release event
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){};
    
    /**
     * Delegate called when the cell is about to be recycled. Immediately
     * after this call the cell will be removed from the scene graph and
     * recycled.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell){};
};

/**
 * Data source that governs table backend data.
 * @lua NA
 */
class CC_DLL CCTableViewDataSource
{
public:
    virtual ~CCTableViewDataSource() {}
    
    /**
     * cell size for a given index
     *
     * @param idx the index of a cell to get a size
     * @return size of a cell at given index
     */
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx) = 0;
    
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx) = 0;
    
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    virtual unsigned int numberOfCellsInTableView(CCTableView *table) = 0;
};

/**
 * The code is copied from CCTableView for fix following:
 * 1. change some method to virtual so that subclass can override it, such as CCTableView
 */
class CC_DLL CCTableView : public CCScrollView, public CCScrollViewDelegate
{
public:
    /**
     *  @js ctor
     */
    CCTableView();
    /**
     *  @js NA
     */
    virtual ~CCTableView();
    
    /**
     * An intialized table view object
     *
     * @param dataSource data source
     * @param size view size
     * @return table view
     */
    static CCTableView* create(CCTableViewDataSource* dataSource, CCSize size);
    /**
     * An initialized table view object
     *
     * @param dataSource data source;
     * @param size view size
     * @param container parent object for cells
     * @return table view
     */
    static CCTableView* create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container);
    
    /**
     * An initialized table view object without specify data source, if you want to use script side
     * data source, this is the method you should call
     *
     * @param size view size
     * @return table view
     */
    static CCTableView* create(CCSize size);
    
    /**
     * data source
     * @js NA
     */
    CCTableViewDataSource* getDataSource() { return m_pDataSource; }
    void setDataSource(CCTableViewDataSource* source) { m_pDataSource = source; }
    /**
     * delegate
     * @js NA
     */
    CCTableViewDelegate* getDelegate() { return m_pTableViewDelegate; }
    void setDelegate(CCTableViewDelegate* pDelegate) { m_pTableViewDelegate = pDelegate; }
    
    
    bool initWithViewSize(CCSize size, CCNode* container = NULL);
    /**
     * Updates the content of the cell at a given index.
     *
     * @param idx index to find a cell
     */
    void updateCellAtIndex(unsigned int idx);
    /**
     * Inserts a new cell at a given index
     *
     * @param idx location to insert
     */
    void insertCellAtIndex(unsigned int idx);
    /**
     * Removes a cell at a given index
     *
     * @param idx index to find a cell
     */
    void removeCellAtIndex(unsigned int idx);
    /**
     * reloads data from data source.  the view will be refreshed.
     * @param keepOffset true means try to keep old content offset, false means
     *      the content offset will be reset to min
     */
    void reloadData(bool keepOffset = false);
    /**
     * Dequeues a free cell if available. nil if not.
     *
     * @return free cell
     */
    CCTableViewCell *dequeueCell(const string& name = "");
    
    /**
     * Returns an existing cell at a given index. Returns nil if a cell is nonexistent at the moment of query.
     *
     * @param idx index
     * @return a cell at a given index
     */
    CCTableViewCell *cellAtIndex(unsigned int idx);
    
    /**
     * determin if a given cell's bound is contained in visible bound
     */
    bool isCellFullyVisible(unsigned int index);
    
    /**
     * determin if a given cell's bound is intersected with visible bound
     */
    bool isCellVisible(unsigned int index);
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    int getRealRows();
    
protected:
    
    CCTableViewCell *m_pTouchedCell;
    
    /**
     * index set to query the indexes of the cells used.
     */
    set<unsigned int>* m_pIndices;
    
    vector<float> m_vCellsPositions; // relative to top
    vector<float> m_hCellsPositions;
    int m_viewRows; // for horizontal
    
    /**
     * cells that are currently in the table
     */
    CCArrayForObjectSorting* m_pCellsUsed;
    /**
     * free list of cells
     */
    CCArrayForObjectSorting* m_pCellsFreed;
    /**
     * weak link to the data source object
     */
    CCTableViewDataSource* m_pDataSource;
    /**
     * weak link to the delegate object
     */
    CCTableViewDelegate* m_pTableViewDelegate;
    
    /// script side table data source and delegate
    ccScriptFunction m_scriptHandler;
    
    virtual int _indexFromOffset(CCPoint offset, bool excludeMargin = false);
    virtual CCPoint _offsetFromIndex(unsigned int index);
    
    void _moveCellOutOfSight(CCTableViewCell *cell);
    void _setIndexForCell(unsigned int index, CCTableViewCell *cell);
    void _addCellIfNecessary(CCTableViewCell * cell);
    void _updateCellPositions();
    virtual void _updateContentSize(bool keepOffset = false);
    
    // event dispatch
    void onTableCellTouched();
    void onTableCellHighlight();
    void onTableCellUnhighlight();
    void onTableCellWillRecycle(CCTableViewCell* cell);
    unsigned int onNumberOfCellsInTableView();
    CCSize onTableCellSizeForIndex(unsigned int idx);
    CCTableViewCell* onTableCellAtIndex(unsigned int idx);
    
    // script returned value collector
    void collectReturnedCCSize();
    void collectReturnedCell();
    
    // temp to save script returned value
    CCSize m_scriptRetSize;
    CCTableViewCell* m_scriptRetCell;
    
public:
    /**
     * get min container offset to make cell at index visible
     *
     * @param index cell index, start from zero
     * @return container offset
     */
    CCPoint containerOffsetFromIndex(unsigned int index);
    
    /**
     register a script side table view data source and delegate. the event is a string passed to
     script side and script function should check first argument(if first is not self) to see what
     happened
     
     lua example code:
     function XXX:onTableViewEvent(tableView, e, ...)
        if e == cc.TableViewEventCellAtIndex then
            -- argument is idx, should return cell
            local idx = ...
            local cell = tableView:dequeueCell()
            if cell == nil then
                cell = CCTableViewCell:create()
            end
            
            -- do init before return
            return cell
        elseif e == cc.TableViewEventCellTouched then
            -- argument is cell
            local cell = ...
        elseif e == cc.TableViewEventCellHighlight then
             -- argument is cell
             local cell = ...
        elseif e == cc.TableViewEventCellUnhighlight then
             -- argument is cell
             local cell = ...
        elseif e == cc.TableViewEventCellWillRecycle then
             -- argument is cell
             local cell = ...
        elseif e == cc.TableViewEventCellSizeForIndex then
            -- argument is idx
            local idx = ...
            
            -- return a size
            return xxx
        elseif e == cc.TableViewEventNumberOfCells then
            -- you should return cell count
            return xxx
        end
     end
     */
    void registerScriptTableViewEventHandler(ccScriptFunction func);
    
    /// unregister script side table view event handler
    void unregisterScriptTableViewEventHandler();
    
    /// column count, by default it is 1
    CC_SYNTHESIZE_SETTER(unsigned int, m_colCount, ColCount);
    
    /// border spacing
    CC_SYNTHESIZE_SETTER(ccInsets, m_insets, Insets);
    
    /// spacing between rows
    CC_SYNTHESIZE_SETTER(float, m_rowSpacing, RowSpacing);
    
    /// spacing between columns
    CC_SYNTHESIZE_SETTER(float, m_colSpacing, ColSpacing);
};

NS_CC_EXT_END

#endif /* __CCTableView__ */
