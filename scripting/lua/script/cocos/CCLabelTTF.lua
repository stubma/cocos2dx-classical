require("script/cocos/overload")

overload.createLabel {
    "string",
    "string",
    "number",
    "number",
    function(text, font, size, color)
        local label = CCLabelTTF:create(text, font, size)
        label:setColor(cc.i2c3b(color))
        return label
    end
}

overload.createLabel {
    "class",
    "table",
    "string",
    "string",
    "number",
    function(parent, pos, text, font, size)
        local label = CCLabelTTF:create(text, font, size)
        label:setPosition(pos)
        parent:addChild(label)
        return label
    end
}

overload.createLabel {
    "class",
    "table",
    "string",
    "string",
    "number",
    "table",
    "number",
    function(parent, pos, text, font, size, dimension, alignment)
        local label = CCLabelTTF:create(text, font, size, dimension, alignment)
        label:setPosition(pos)
        parent:addChild(label)
        return label
    end
}

overload.createLabel {
    "class",
    "table",
    "string",
    "string",
    "number",
    "table",
    "number",
    "table",
    "number",
    "number",
    function(parent, pos, text, font, size, dimension, alignment, color, z, tag)
        local label = CCLabelTTF:create(text, font, size, dimension, alignment)
        label:setPosition(pos)
        label:setColor(color)
        parent:addChild(label, z, tag)
        return label
    end
}