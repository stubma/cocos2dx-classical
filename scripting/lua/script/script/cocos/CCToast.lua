require("script/cocos/overload")

cc = cc or {}

function cc.createSingleLineFadeInToast(parent, msg)
    local hintLabel = CCLabelTTF:create(msg, "Helvetica", 28 / display.factor)
    local hintSize = hintLabel:getContentSize()
    local bg = CCLayerColor:create(cc.c4b(0, 0, 0, 200))
    bg:ignoreAnchorPointForPosition(false)
    local bgSize = cc.size(hintSize.width * 1.4, hintSize.height * 1.4)
    bg:setContentSize(bgSize)
    hintLabel:setPosition(CCUtils:getLocalCenter(bg))
    bg:addChild(hintLabel)
    local t = CCToast:create(parent, bg)
    t:setPosition(cc.p(display.CENTER.x,
                       display.origin.y + display.visibleSize.height / 5))
end