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
        tolua.cast(obj, type)
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
        tolua.cast(obj, type)
        if handler ~= nil then
            obj:addScriptTouchEventListener(handler)
        end
        return obj
    end
}
