function cc.createLabel(name, x, y, aX, aY, parent, tag, size, color)
    local ccFontDefinition = { m_fontName = "SIMHEI", m_fontSize = 120, m_dimensions = {1,0} }
    local nameLabel = CCLabelTTF:createWithFontDefinition("test", ccFontDefinition);
    nameLabel:setString(name)
    nameLabel:setFontSize(size)
    nameLabel:setDimensions(cc.p(1, 0))
    nameLabel:setFontName("SIMHEI")
    cc.setAnchor(nameLabel, aX, aY)
    nameLabel:setColor(cc.i2c3b(color), true);
    nameLabel:setPosition(x, y);
    parent:addChild(nameLabel, tag);
    return nameLabel
end