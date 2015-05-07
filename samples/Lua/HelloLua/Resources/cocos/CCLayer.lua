function cc.createLayer(parent, x, y, z, tag)
    local layer = CCLayer:create()
    layer:setPosition(x, y)
    parent:addChild(layer, z, tag)
    return layer
end