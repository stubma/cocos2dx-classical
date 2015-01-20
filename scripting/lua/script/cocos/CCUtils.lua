function R(name)
    return CCUtils:getExternalOrFullPath(name)
end

function cc.isEmpty(s)
    return s == nil or s == ""
end