function cc.delayActionN(node, time, callback)
    node:runAction(CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                   CCCallFuncN:create(callback)))
end

function cc.delayAction(node, time, callback)
    node:runAction(CCSequence:createWithTwoActions(CCDelayTime:create(time),
                                                   CCCallFunc:create(callback)))
end