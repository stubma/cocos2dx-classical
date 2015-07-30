debug = debug or {}

-- trace filter, whitelist
local trace_filter_file_whitelist = {}

-- print program execution line, used by debug.sethook(debug._tracehook, "l")
function debug._tracehook(event, line)
    -- try to get file name
    local t = debug.getinfo(2, "Sn")
    local file = nil
    if t.source then
        local s,e,_ = string.find(t.source, "/[_%w%.]+$")
        if s ~= nil then
            file = string.sub(t.source, s + 1, e)
        end
    end
    
    -- if file name is got, ensure it is in whitelist
    if file then
        -- check whitelist
        if trace_filter_file_whitelist[file] == nil then
            return
        end
        
        -- print trace log
        if t.name then
            print(file .. ":" .. t.name .. ", line " .. line)
        else
            print(file .. ", line " .. line)
        end
    end
end

-- add a file to trace filter, so that it print function and line number
-- when executing in that file
function debug.addtrace(file)
    trace_filter_file_whitelist[file] = true
end

-- remove a file from trace filter, i.e., don't print trace log for this file
function debug.removetrace(file)
    trace_filter_file_whitelist[file] = nil
end