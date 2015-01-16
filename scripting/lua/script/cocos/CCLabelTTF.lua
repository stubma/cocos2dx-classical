function cc.createLabel(name, x, y, anchor, parent, tag, size, color)
    local ccFontDefinition = { m_fontName = "SIMHEI", m_fontSize = 120, m_dimensions = {1,0} }
    local nameLabel = CCLabelTTF:createWithFontDefinition("test", ccFontDefinition);
    nameLabel:setString(name)
    nameLabel:setFontSize(size)
    nameLabel:setDimensions(ccp(1, 0))
    nameLabel:setFontName("SIMHEI")
    ccsetAnchor(nameLabel, anchor)
    nameLabel:setColor(ccgetRGB(color), true);
    nameLabel:setPosition(x, y);
    parent:addChild(nameLabel, tag);
    return nameLabel
end