-- anchor is a table, x = ?, y = ?
function cc.setAnchor(node, anchor)
    node:setAnchorPoint(anchor)
end

function cc.setAnchor(node, x, y)
    node:setAnchorPoint({ x = x, y = y })
end

function cc.delayActionN(node, time, callback)
    local sequence = CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                     CCCallFuncN:create(callback));
    node:runAction(sequence)
    return sequence
end

function cc.delayAction(node, time, callback)
    local sequence = CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                     CCCallFunc:create(callback))
    node:runAction(sequence)
    return sequence
end