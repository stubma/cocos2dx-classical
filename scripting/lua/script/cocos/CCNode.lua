-- anchor is a table, x = ?, y = ?
function cc.setAnchor(node, anchor)
    node:setAnchorPoint(anchor)
end

function cc.setAnchor(node, x, y)
    node:setAnchorPoint({ x = x, y = y })
end

function cc.delayActionN(node, time, callback)
    node:runAction(CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                   CCCallFuncN:create(callback)))
end

function cc.delayAction(node, time, callback)
    node:runAction(CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                   CCCallFunc:create(callback)))
end