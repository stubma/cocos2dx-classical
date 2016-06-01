-- clone a lua object, whatever the type it is
function clone(object)
    local lookup_table = {}
    local function _copy(object)
        if type(object) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        local new_table = {}
        lookup_table[object] = new_table
        for key, value in pairs(object) do
            new_table[_copy(key)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(object))
    end
    return _copy(object)
end

-- declare a class, the super can be a function which returns a user type or
-- a table. it will return class itself, which actually is a table too
local CC_INHERITED_FROM_NATIVE_CLASS = 1
local CC_INHERITED_FROM_LUA = 2
function class(classname, super)
    local superType = type(super)
    local cls = {}

    if superType ~= "function" and superType ~= "table" then
        superType = nil
        super = nil
    end

    -- call ctor in inheritance sequence
    function callCtor(instance, super, ...)
        if super ~= nil then
            if super.super ~= nil then
                callCtor(instance, super.super, ...)
            end
            if super.ctor ~= nil then
                super.ctor(instance, ...)
            end
        end
    end

    if superType == "function" or (super and super.__ctype == CC_INHERITED_FROM_NATIVE_CLASS) then
        if superType == "table" then
            -- copy fields from super
            for k,v in pairs(super) do cls[k] = v end
            cls.__create = super.__create
            cls.super    = super
        else
            cls.__create = super
        end

        cls.ctor = function() end
        cls.dtor = function() end
        cls.__cname = classname
        cls.__ctype = CC_INHERITED_FROM_NATIVE_CLASS

        function cls.new(...)
            local instance = cls.__create(...)
            
            -- copy fields from class to native object
            for k,v in pairs(cls) do
                instance[k] = v
            end
            
            -- ctor
            instance.class = cls
            callCtor(instance, instance.super, ...)
            instance:ctor(...)
            return instance
        end
    else
        -- inherited from Lua Object
        if super then
            cls = clone(super)
            cls.super = super
        else
            cls.super = {}
        end

        cls.ctor = function() end
        cls.dtor = function() end
        cls.__cname = classname
        cls.__ctype = CC_INHERITED_FROM_LUA
        cls.__index = cls

        function cls.new(...)
            local instance = setmetatable({}, cls)
            instance.class = cls
            
            -- ctor
            callCtor(instance, instance.super, ...)
            instance:ctor(...)
            return instance
        end
    end

    return cls
end

-- bridge accessor invocation to a bean member
function bridgeAccessor(srcClass, beanClass, beanName, postSet)
    for k,v in pairs(beanClass) do
        if type(v) == "function" then
            if string.startswith(k, "is") or
                string.startswith(k, "get") or
                string.startswith(k, "has") then
                srcClass[k] = function(instance, ...)
                    return v(instance[beanName], ...)
                end
            elseif string.startswith(k, "set") then
                srcClass[k] = function(instance, ...)
                    v(instance[beanName], ...)
                    if postSet ~= nil then
                        postSet(instance)
                    end
                end
            end
        end
    end
end

-- reverse iterate a table
function ripairs(t)
    local max = 1
    while t[max] ~= nil do
        max = max + 1
    end
    local function ripairs_it(t, i)
        i = i-1
        local v = t[i]
        if v ~= nil then
            return i,v
        else
            return nil
        end
    end
    return ripairs_it, t, max
end

-- get real size of a table or other type, if nil, return 0
function len(t)
    if t == nil then
        return 0
    elseif type(t) == "table" then
        local c = 0
        for _,v in pairs(t) do
            c = c + 1
        end
        return c
    else
        return #t
    end
end

-- change a table to readonly
function const(value)
    -- set table member recursively
    table.foreach(value, function(i, v)
                  if type(v) == "table" then
                    const(v)
                  end
              end)

    -- make table readonly
    local t = {}
    local mt = {
        __index = value,
        __newindex = function (t,k,v)
            print("can't update " .. tostring(t) .. "[" .. tostring(k) .. "] = " .. tostring(v))
        end
    }
    return setmetatable(t, mt)
end