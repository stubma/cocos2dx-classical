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

-- fill a table with dummy values, elements after length will be kept
function table.fill(t, v, len)
    if t then
        for i = 1, len do
            t[i] = v
        end
    end
end

-- return a filled table
function table.fillnew(v, len)
    local t = {}
    for i = 1, len do
        t[i] = v
    end
    return t
end