require("script/cocos/overload")

overload.createSprite {
    "class",
    "string",
    "table",
    function(parent, name, pos)
        local sprite = CCSprite:create(name)
        sprite:setPosition(pos)
        if tolua.isa(parent, "Widget") then
            parent:addNode(sprite)
        else
            parent:addChild(sprite)
        end
        return sprite
    end
}

overload.createSprite {
    "class",
    "string",
    "table",
    "table",
    "number",
    "number",
    function(parent, name, pos, anchor, z, tag)
        local sprite = CCSprite:create(name)
        sprite:setPosition(pos)
        cc.setAnchor(sprite, anchor.x, anchor.y)
        if tolua.isa(parent, "Widget") then
            parent:addNode(sprite, z, tag)
        else
            parent:addChild(sprite, z, tag)
        end
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
        if tolua.isa(parent, "Widget") then
            parent:addNode(sprite)
        else
            parent:addChild(sprite)
        end
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
        if tolua.isa(parent, "Widget") then
            parent:addNode(sprite, z, tag)
        else
            parent:addChild(sprite, z, tag)
        end
        return sprite
    end
}