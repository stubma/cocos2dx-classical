function cc.createSprite(name, x, y, aX, aY, parent, tag)
    local sprite = CCSprite:create(name)
    sprite:setPosition(x, y)
    cc.setAnchor(sprite, aX, aY)
    parent:addChild(sprite, tag)
    return sprite
end

function cc.createFrameSprite(name, x, y, aX, aY, parent, tag)
    local sprite = CCSprite:createWithSpriteFrameName(name)
    sprite:setPosition(x, y)
    cc.setAnchor(sprite, aX, aY)
    parent:addChild(sprite, tag)
    return sprite
end

function createWidgetSprite(name, x, y, aX, aY, parent)
    local sprite = CCSprite:create(name)
    sprite:setPosition(x, y)
    cc.setAnchor(sprite, aX, aY)
    parent:addNode(sprite)
    return sprite
end