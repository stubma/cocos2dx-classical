local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)

    -- initialize director
    local d = CCDirector:sharedDirector()
    d:setOpenGLView(CCEGLView:sharedOpenGLView())

    -- set resolution size and mode
    -- 2 is cc.ResolutionNoBorder, but this is happened before requireAllScript so we need use number
    -- we can't move requireAllScript ahead because resolution size must be set before loading cocos scripts
    CCEGLView:sharedOpenGLView():setDesignResolutionSize(480, 320, 1)

    -- load cocos scripts
    require("script/cocos/__init__")
    loadLua("ui")

    -- surface size
    local visibleSize = display.visibleSize
    local origin = display.origin

    -- create menu
    local function createLayerMenu()
        local layerMenu = CCLayer:create()

        local menuPopup, menuTools, effectID

        local function menuCallbackClosePopup()
            -- stop test sound effect
            SimpleAudioEngine:sharedEngine():stopEffect(effectID)
            menuPopup:setVisible(false)
        end

        local function menuCallbackOpenPopup()
            -- loop test sound effect
            local effectPath = CCFileUtils:sharedFileUtils():fullPathForFilename("effect1.wav")
            effectID = SimpleAudioEngine:sharedEngine():playEffect(effectPath)
            menuPopup:setVisible(true)
        end

        -- add a popup menu
        local menuPopupItem = CCMenuItemImage:create("menu2.png", "menu2.png")
        menuPopupItem:setPosition(0, 0)
        menuPopupItem:registerScriptTapHandler(menuCallbackClosePopup)
        menuPopup = CCMenu:createWithItem(menuPopupItem)
        menuPopup:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)
        menuPopup:setVisible(false)
        layerMenu:addChild(menuPopup)

        -- add the left-bottom "tools" menu to invoke menuPopup
        local menuToolsItem = CCMenuItemImage:create("menu1.png", "menu1.png")
        menuToolsItem:setPosition(0, 0)
        menuToolsItem:registerScriptTapHandler(menuCallbackOpenPopup)
        menuTools = CCMenu:createWithItem(menuToolsItem)
        local itemWidth = menuToolsItem:getContentSize().width
        local itemHeight = menuToolsItem:getContentSize().height
        menuTools:setPosition(origin.x + itemWidth/2, origin.y + itemHeight/2)
        layerMenu:addChild(menuTools)

        return layerMenu
    end

    -- play background music, preload effect
	local bgMusicPath = CCFileUtils:sharedFileUtils():fullPathForFilename("background.mp3")
	AudioEngine.playMusic(bgMusicPath, true)
    local effectPath = CCFileUtils:sharedFileUtils():fullPathForFilename("effect1.wav")
    AudioEngine.preloadEffect(effectPath)
	
    -- run
    local sceneGame = CCScene:create()
    sceneGame:addChild(FarmLayer.new())
    sceneGame:addChild(createLayerMenu())
    CCDirector:sharedDirector():runWithScene(sceneGame)
end

function applicationDidEnterBackground()
    CCDirector:sharedDirector():stopAnimation()
    AudioEngine.pauseMusic()
end

function applicationWillEnterForeground()
    CCDirector:sharedDirector():startAnimation()
    AudioEngine.resumeMusic()
end

xpcall(main, __G__TRACKBACK__)
