require("script/cocos/Cocos2d")

display = display or {}

local sharedDirector = CCDirector:sharedDirector()
display.winSize = sharedDirector:getWinSize()
display.visibleSize = sharedDirector:getVisibleSize()
display.origin = sharedDirector:getVisibleOrigin()
display.factor = sharedDirector:getContentScaleFactor()
display.safeAreaInsets = sharedDirector:getSafeAreaInsets()
display.safeArea = sharedDirector:getSafeArea()
display.CENTER = cc.p(display.origin.x + display.visibleSize.width / 2,
                      display.origin.y + display.visibleSize.height / 2)

function display.getRunningScene()
    return sharedDirector:getRunningScene()
end

function display.pause()
    sharedDirector:pause()
end

function display.resume()
    sharedDirector:resume()
end

function display.smoothAnimation()
    sharedDirector:setNextDeltaTimeZero(true)
end
