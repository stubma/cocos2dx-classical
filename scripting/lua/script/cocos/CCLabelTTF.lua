function cc.createLabel(parent, name, x, y, aX, aY, z, tag, size, color)
    local nameLabel = CCLabelTTF:create(name, "SIMHEI", 120)
    nameLabel:setDimensions(cc.p(1, 0))
    cc.setAnchor(nameLabel, aX, aY)
    nameLabel:setColor(cc.i2c3b(color))
    nameLabel:setPosition(x, y)
    parent:addChild(nameLabel, z, tag)
    return nameLabel
end