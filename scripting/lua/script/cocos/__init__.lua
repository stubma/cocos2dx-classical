cc = cc or {}

-- platform constants, they are required by __init__ so move them here
cc.PLATFORM_UNKNOWN            = 0
cc.PLATFORM_IOS                = 1
cc.PLATFORM_ANDROID            = 2
cc.PLATFORM_WIN32              = 3
cc.PLATFORM_MARMALADE          = 4
cc.PLATFORM_LINUX              = 5
cc.PLATFORM_BADA               = 6
cc.PLATFORM_BLACKBERRY         = 7
cc.PLATFORM_MAC                = 8
cc.PLATFORM_NACL               = 9
cc.PLATFORM_EMSCRIPTEN        = 10
cc.PLATFORM_TIZEN             = 11
cc.PLATFORM_WINRT             = 12
cc.PLATFORM_WP8               = 13

-- cc.log
function cc.log(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cc.log("----------------------------------------")
    cc.log("LUA ERROR: " .. tostring(msg))
    cc.log(debug.traceback())
    cc.log("----------------------------------------")
    
    -- show a layer to error message and stack, make it easy for developer to fix it
    if Version:isDebug() then
        local scene = display.getRunningScene()
        if scene then
            local layer = CCLayerColor:create(cc.cc4WHITE)
            scene:addChild(layer, Z_UI)
            local errLabel = CCLabelTTF:create(tostring(msg) .. "\n" .. debug.traceback(),
                                               FONT_SIMHEI,
                                               20,
                                               cc.size(display.visibleSize.width * 0.95, 0),
                                               cc.TextAlignmentLeft)
            errLabel:setPosition(CCUtils:getLocalPoint(layer, 0.5, 0.95))
            errLabel:setAnchorPoint(cc.p(0.5, 1))
            errLabel:setColor(cc.ccBLACK)
            layer:addChild(errLabel)
        end
    end
end

-- load lua file under a folder, include subfolders
function loadLua(name)
    -- internal and external path
    local internalPath
    if CCDevice:getPlatform() == cc.PLATFORM_ANDROID then
        internalPath = "script" .. "/" .. name
    else
        internalPath = CCFileUtils:sharedFileUtils():fullPathForFilename("script") .. "/" .. name
    end
    local externalPath = CCUtils:externalize("script")  .. "/" .. name
    
    -- search file in internal and external, exclude duplicated entry
    local entries = {}
    local internalEntries = {}
    if CCDevice:getPlatform() == cc.PLATFORM_ANDROID then
        internalEntries = CCFileUtils:sharedFileUtils():listAssets(internalPath)
        for _,entry in ipairs(internalEntries) do
            local isLua = entry ~= "__init__.lua" and string.find(entry, ".lua") ~= nil
            local isLc = entry ~= "__init__.lc" and string.find(entry, ".lc") ~= nil
            if entry ~= "." and entry ~= ".." and (isLua or isLc) then
                local s, n = string.gsub(entry, "%.lua+", "")
                s, n = string.gsub(s, "%.lc+", "")
                entries[tostring(s)] = internalPath
            end
        end
    else
        internalEntries = lfs.dir(internalPath)
        for entry in internalEntries do
            local isLua = entry ~= "__init__.lua" and string.find(entry, ".lua") ~= nil
            local isLc = entry ~= "__init__.lc" and string.find(entry, ".lc") ~= nil
            if entry ~= "." and entry ~= ".." and (isLua or isLc) then
                local s, n = string.gsub(entry, "%.lua+", "")
                s, n = string.gsub(s, "%.lc+", "")
                entries[tostring(s)] = internalPath
            end
        end
    end
    if CCUtils:isPathExistent(externalPath) then
        for entry in lfs.dir(externalPath) do
            local isLua = entry ~= "__init__.lua" and string.find(entry, ".lua") ~= nil
            local isLc = entry ~= "__init__.lc" and string.find(entry, ".lc") ~= nil
            if entry ~= "." and entry ~= ".." and (isLua or isLc) then
                local s, n = string.gsub(entry, "%.lua+", "")
                s, n = string.gsub(s, "%.lc+", "")
                entries[tostring(s)] = externalPath
            end
        end
    end
    
    -- load
    for file,path in pairs(entries) do
        local fullpath = path .. "/" .. file
        require(fullpath)
    end
end

-- load all cocos core lua
loadLua("cocos")