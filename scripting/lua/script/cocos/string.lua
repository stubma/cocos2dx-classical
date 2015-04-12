string = string or {}

-- safe convert a string to number, never return nil
function string.tonumber(s)
    local n = tonumber(s)
    if n == nil then
        return 0
        else
        return n
    end
end

-- safe convert a string to integer, never return nil
function string.toint(s)
    return math.floor(string.tonumber(s))
end

-- convert a string to bool
function string.tobool(s)
    local x = string.lower(tostring(s))
    return x == "y" or x == "true" or string.tonumber(x) > 0
end