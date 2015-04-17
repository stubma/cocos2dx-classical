string = string or {}

-- safe convert a string to number, never return nil
function string.tonumber(s, def)
    local n = tonumber(s)
    if n == nil then
        return def == nil and 0 or def
    else
        return n
    end
end

-- safe convert a string to integer, never return nil
function string.toint(s, def)
    return math.floor(string.tonumber(s, def))
end

-- convert a string to bool
function string.tobool(s)
    local x = string.lower(tostring(s))
    return x == "y" or x == "yes" or x == "true" or string.tonumber(x) > 0
end

-- check string empty, empty means it is nil or zero length string
function string.empty(s)
    return s == nil or string.len(s) <= 0
end

-- check a string starts with a pattern
function string.startswith(s, pattern)
    return s ~= nil and string.find(s, pattern) == 1
end