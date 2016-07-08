string = string or {}

-- split a string by a separator, and returns a table contains all parts of it
function string.split(s, sep)
    local parts = {}
    local len = string.len(s)
    local sepByte = string.byte(sep and sep or ",", 1)
    local start = 0
    local i = 1
    while i <= len do
        -- get char and check utf8
        local c = string.byte(s, i)
        local charLen = CCUtils:getUTF8Bytes(c)

        -- if c is separator char
        if charLen == 1 and c == sepByte then
            if i <= start + 1 then
                table.insert(parts, "")
            else
                table.insert(parts, string.sub(s, start + 1, i - 1))
            end
            start = i
        end
        
        -- increase i
        i = i + charLen
    end
    if len > 0 then
        if start == len then
            table.insert(parts, "")
        elseif start < len then
            table.insert(parts, string.sub(s, start + 1, len))
        end
    end
    return parts
end

-- safe convert a string to number, never return nil
function string.tonumber(s, def)
    local n = tonumber(s)
    if n == nil then
        return def ~= nil and def or 0
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