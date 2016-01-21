cc = cc or {}

function cc.delayActionN(node, time, callback)
    local sequence = nil
    if type(callback) == "function" then
        sequence = CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                         CCCallFuncN:create(callback))
    else
        sequence = CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                         callback)
    end
    
    node:runAction(sequence)
    return sequence
end

function cc.delayAction(node, time, callback)
    local sequence = nil
    if type(callback) == "function" then
        sequence = CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                   CCCallFunc:create(callback))
    else
        sequence = CCSequence:createWithTwoActions(CCDelayTime:create(time), callback)
    end
    
    node:runAction(sequence)
    return sequence
end

function cc.localX(node, px)
    return CCUtils:getLocalPoint(node, px, 0).x
end

function cc.localY(node, py)
    return CCUtils:getLocalPoint(node, 0, py).y
end

function cc.parentX(node, px)
    return CCUtils:getPoint(node, px, 0).x
end

function cc.parentY(node, py)
    return CCUtils:getPoint(node, 0, py).y
end