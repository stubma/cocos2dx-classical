function cc.createSprite(name, x, y, anchor, parent, tag)
    local sprite = CCSprite:create(name)
    sprite:setPosition(x, y)
    sprite:setAnchorPoint(anchor)
    parent:addChild(sprite, tag)
    return sprite
end

function cc.createFrameSprite(name, x, y, anchor, parent, tag)
    local sprite = CCSprite:createWithSpriteFrameName(name)
    sprite:setPosition(x, y)
    sprite:setAnchorPoint(anchor)
    parent:addChild(sprite, tag)
    return sprite
end

function createWidgetSprite(name, x, y, anchor, parent)
    local sprite = CCSprite:create(name)
    sprite:setPosition(x, y)
    sprite:setAnchorPoint(anchor)
    parent:addNode(sprite)
    return sprite
end