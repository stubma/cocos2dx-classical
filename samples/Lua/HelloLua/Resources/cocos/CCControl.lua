function cc.createControlButton(parent, normal, selected, title, x, y, z, tag, handler)
    local button
    if title == nil then
        button = CCControlButton:create(CCScale9Sprite:createWithSpriteFrame(normal:displayFrame()))
    else
        button = CCControlButton:create(title, CCScale9Sprite:createWithSpriteFrame(normal:displayFrame()))
    end
    button:setPreferredSize(normal:getContentSize())
    button:setBackgroundSpriteFrameForState(selected:displayFrame(), cc.ControlStateHighlighted)
    button:addHandleOfControlEvent(handler, cc.ControlEventTouchUpInside)
    button:setPosition(x, y)
    parent:addChild(button, z, tag)
    return button
end