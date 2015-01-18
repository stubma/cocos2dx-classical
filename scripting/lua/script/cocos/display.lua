display = {}

local sharedDirector         = CCDirector:sharedDirector()
local sharedTextureCache     = CCTextureCache:sharedTextureCache()
local sharedSpriteFrameCache = CCSpriteFrameCache:sharedSpriteFrameCache()
local sharedAnimationCache   = CCAnimationCache:sharedAnimationCache()

display.visibleSize = sharedDirector:getVisibleSize()
display.origin = sharedDirector:getVisibleOrigin()
display.factor = sharedDirector:getContentScaleFactor()
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