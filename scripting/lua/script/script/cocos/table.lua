table = table or {}

-- print all table elements including nested table
function table.print(value, ...)
    local indent = ...
    if indent == nil then
        indent = ""
    end
    table.foreach(value,
                  function(i, v)
                    if type(v) == "table" and v ~= value then
                        print(indent .. i)
                        table.print(v, indent .. "\t")
                    else
                        print(indent .. i .. " = " .. tostring(v))
                    end
                  end)
end

-- check whether a number is existent in a table
-- it will convert other type to number before comparing
function table.hasnumber(t, n)
    n = string.tonumber(n)
    for _,item in ipairs(t) do
        if string.tonumber(item) == n then
            return true
        end
    end
    return false
end

-- check whether a string is existent in a table
-- it will convert other string to number before comparing
function table.hasstring(t, s)
    s = tostring(s)
    for _,item in ipairs(t) do
        if tostring(item) == s then
            return true
        end
    end
    return false
end

--[[
 fill a table with values, old elements in table after len will be kept
 if v is a table, first len items will be copied. or, if v length is shorter
 than len, 0 will be filled
 if v is a value, it will be copied len times
 it returns table itself
--]]
function table.fill(t, v, len)
    if t then
        if type(v) == "table" then
            local m = math.min(len, #v)
            for i = 1, m do
                t[i] = v[i]
            end
            for i = m + 1, len do
                t[i] = 0
            end
        else
            for i = 1, len do
                t[i] = v
            end
        end
    end
    return t
end

-- return a filled table, the logic is same as table.fill but it will return a new table
function table.fillnew(v, len)
    local t = {}
    table.fill(t, v, len)
    return t
end

-- convert string members in t to a enum value, if startValue is not provided, it will
-- start from 1
function table.enum(t, startValue)
    if type(t) == "table" then
        local enumtbl = {}
        local enumindex = (startValue or 1) - 1
        for i,v in ipairs(t) do
            enumtbl[v] = enumindex + i
            enumtbl[enumindex + i] = v
        end
        return enumtbl
    else
        return {}
    end
end