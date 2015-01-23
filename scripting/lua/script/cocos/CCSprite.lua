require("script/cocos/overload")

overload.createSprite {
    "class",
    "string",
    "table",
    function(parent, name, pos)
        local sprite = CCSprite:create(name)
        sprite:setPosition(pos)
        parent:addChild(sprite)
        return sprite
    end
}

overload.createSprite {
    "class",
    "string",
    "number",
    "number",
    function(parent, name, x, y)
        local sprite = CCSprite:create(name)
        sprite:setPosition(x, y)
        parent:addChild(sprite)
        return sprite
    end
}

overload.createSprite {
    "class",
    "string",
    "number",
    "number",
    "number",
    "number",
    "number",
    "number",
    function(parent, name, x, y, aX, aY, z, tag)
        local sprite = CCSprite:create(name)
        sprite:setPosition(x, y)
        cc.setAnchor(sprite, aX, aY)
        parent:addChild(sprite, z, tag)
        return sprite
    end
}

overload.createFrameSprite {
    "string",
    function(name)
        local sprite = CCSprite:createWithSpriteFrameName(name)
        return sprite
    end
}

overload.createFrameSprite {
    "class",
    "string",
    "table",
    function(parent, name, pos)
        local sprite = CCSprite:createWithSpriteFrameName(name)
        sprite:setPosition(pos)
        parent:addChild(sprite)
        return sprite
    end
}

overload.createFrameSprite {
    "class",
    "string",
    "table",
    "table",
    "number",
    "number",
    function(parent, name, pos, anchor, z, tag)
        local sprite = CCSprite:createWithSpriteFrameName(name)
        sprite:setPosition(pos)
        cc.setAnchor(sprite, anchor.x, anchor.y)
        parent:addChild(sprite, z, tag)
        return sprite
    end
}

function cc.createWidgetSprite(parent, name, x, y, aX, aY, z, tag)
    local sprite = CCSprite:create(name)
    sprite:setPosition(x, y)
    cc.setAnchor(sprite, aX, aY)
    parent:addNode(sprite, z, tag)
    return sprite
end