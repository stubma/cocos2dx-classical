require("script/cocos/overload")

define.createSprite {
    "string",
    "number",
    "number",
    "number",
    "number",
    "class",
    "number",
    "number",
    function(name, x, y, aX, aY, parent, z, tag)
        local sprite = CCSprite:create(name)
        sprite:setPosition(x, y)
        cc.setAnchor(sprite, aX, aY)
        parent:addChild(sprite, z, tag)
        return sprite
    end
}

function cc.createFrameSprite(name, x, y, aX, aY, parent, z, tag)
    local sprite = CCSprite:createWithSpriteFrameName(name)
    sprite:setPosition(x, y)
    cc.setAnchor(sprite, aX, aY)
    parent:addChild(sprite, z, tag)
    return sprite
end

function createWidgetSprite(name, x, y, aX, aY, parent, z, tag)
    local sprite = CCSprite:create(name)
    sprite:setPosition(x, y)
    cc.setAnchor(sprite, aX, aY)
    parent:addNode(sprite, z, tag)
    return sprite
end