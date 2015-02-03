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
cc.log = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cc.log("----------------------------------------")
    cc.log("LUA ERROR: " .. tostring(msg) .. "\n")
    cc.log(debug.traceback())
    cc.log("----------------------------------------")
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