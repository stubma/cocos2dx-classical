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

-- raw check whether an element is existent in a table
-- it doesn't force type checking
function table.has(t, v)
    for _,item in ipairs(t) do
        if item == v then
            return true
        end
    end
    return false
end

-- check whether a number is existent in a table
-- it force type checking, so matched element must have number type
function table.hasnumber(t, n)
    for _,item in ipairs(t) do
        if type(item) == "number" and item == n then
            return true
        end
    end
    return false
end

-- check whether a string is existent in a table
-- it force type checking, so matched element must have string type
function table.hasstring(t, s)
    for _,item in ipairs(t) do
        if type(item) == "string" and item == n then
            return true
        end
    end
    return false
end

--[[
 fill a table with values, old elements in table will be cleared
 if v is a table, first len items will be copied. or, if v length is shorter
 than len, 0 will be filled
 if v is a value, it will be copied len times
 it returns table itself
--]]
function table.fill(t, v, len)
    if t then
        t = {}
        if type(v) == "table" then
            local m = math.min(len, #v)
            for i = 1, m then
                t[i] = v[i]
            end
            for i = m + 1, len then
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