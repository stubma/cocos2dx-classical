require("script/cocos/overload")

ccs = ccs or {}

-- movement type
cc.START = 0
cc.COMPLETE = 1
cc.LOOP_COMPLETE = 2

-- layout color type
cc.LAYOUT_COLOR_NONE = 0
cc.LAYOUT_COLOR_SOLID = 1
cc.LAYOUT_COLOR_GRADIENT = 2

-- layout parameter
cc.LAYOUT_PARAMETER_NONE = 0
cc.LAYOUT_PARAMETER_LINEAR = 1
cc.LAYOUT_PARAMETER_RELATIVE = 2

-- texture type
cc.UI_TEX_TYPE_LOCAL = 0
cc.UI_TEX_TYPE_PLIST = 1

-- widget bright style
cc.BRIGHT_NONE = -1
cc.BRIGHT_NORMAL = 0
cc.BRIGHT_HIGHLIGHT = 1

overload.createArm {
    "class",
    "string",
    "string",
    "table",
    function(parent, arm, anim, pos)
        local a = CCArmature:create(arm)
        a:getAnimation():play(anim)
        a:setPosition(pos)
        parent:addChild(a)
        return a
    end
}

overload.createArm {
    "class",
    "string",
    "string",
    "table",
    "number",
    "number",
    function(parent, arm, anim, pos, z, tag)
        local a = CCArmature:create(arm)
        a:getAnimation():play(anim)
        a:setPosition(pos)
        parent:addChild(a, z, tag)
        return a
    end
}

overload.getWidgetByName {
    "class",
    "string",
    function(root, name)
        local obj = UIHelper:seekWidgetByName(root, name)
        return obj
    end
}

overload.getWidgetByName {
    "class",
    "string",
    "string",
    function(root, name, type)
        local obj = UIHelper:seekWidgetByName(root, name)
        if obj ~= nil then
            tolua.cast(obj, type)
        end
        return obj
    end
}

overload.getWidgetByName {
    "class",
    "string",
    "string",
    "table",
    function(root, name, type, handler)
        local obj = UIHelper:seekWidgetByName(root, name)
        if obj ~= nil then
            tolua.cast(obj, type)
            if handler ~= nil then
                obj:addScriptTouchEventListener(handler)
            end
        end
        return obj
    end
}
