ccs = ccs or {}

-- movement type
ccs.START = 0
ccs.COMPLETE = 1
ccs.LOOP_COMPLETE = 2

function ccs.createArm(arm, anim, x, y, parent, tag, z)
    local a = CCArmature:create(arm)
    a:getAnimation():play(anim)
    a:setPosition(x, y)
    parent:addChild(a, tag, z)
    return a
end