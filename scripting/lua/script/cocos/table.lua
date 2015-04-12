table = table or {}

-- join table
function table.join(t, sep)
    local s = ""
    for _,item in ipairs(t) do
        if string.len(s) > 0 then
            s = s .. sep
        end
        s = s .. tostring(item)
    end
    return s
end