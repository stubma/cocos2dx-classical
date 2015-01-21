require("script/cocos/overload")

ccs = ccs or {}

-- movement type
ccs.START = 0
ccs.COMPLETE = 1
ccs.LOOP_COMPLETE = 2

function ccs.createArm(arm, anim, x, y, parent, z, tag)
    local a = CCArmature:create(arm)
    a:getAnimation():play(anim)
    a:setPosition(x, y)
    parent:addChild(a, z, tag)
    return a
end

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
