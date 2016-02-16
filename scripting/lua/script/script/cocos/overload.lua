cc = cc or {}

local function create()
    local arg_table = {}
    local function dispatcher (...)
        local tbl = arg_table
        local n = select ("#", ...)
        local last_match
        for i = 1, n do
            local t = type(select(i, ...))
            local n = tbl[t]
            if (t == "userdata" or t == "table") and not n then
                n = tbl["class"]
            end
            last_match = tbl["..."] or last_match
            if not n then
                return last_match(...)
            end
            tbl = n
        end
        return (tbl["__end"] or tbl["..."])(...)
    end
    local function register(desc, func)
        local tbl = arg_table
        for _,v in ipairs(desc) do
            if v == "..." then
                assert(not tbl["..."])
                tbl["..."] = func
                return
            end
            
            local n = tbl[v]
            if not n then
                n = {}
                tbl[v] = n
            end
            tbl = n
        end
        tbl["__end"] = func
    end
    return dispatcher, register, arg_table
end

local all = {}

local function register(desc, name)
    -- function should be last element in desc
    local func = desc[#desc]
    assert(type(func) == "function")
    table.remove(desc)
    
    -- decide package name, if not specified, put it in cc
    local env = desc[#desc]
    if type(env) ~= "table" then
        env = cc
    else
        table.remove(desc)
    end
    
    -- find register table by package name, if not existent, create new one
    local reg_func_table
    if all[env] then
        reg_func_table = all[env]
    else
        reg_func_table = {}
        all[env] = reg_func_table
    end
    
    -- save dispatcher and register, so when you call
    -- function by env.name, it actually calls dispatcher
    if env[name] then
        assert(reg_func_table[name])
    else
        env[name], reg_func_table[name] = create()
    end
    
    -- register function by argument chain
    reg_func_table[name](desc, func)
end

--[[ 
    define overload function in cc module
    example usage:
    overload.testFunction {
        "string",
        "table", -- for lua table
        "class", -- for userdata or table
        package_name, -- optional, if not set, the test function is put in cc namespace by default
        function(s, t, c)
            -- put your code
        end
    }
    and call it with package_name.testFunction(...)
    
    function should be placed in the end, and put every argument type string
    before it. argument type string can be "number", "string", "table", "userdata", "...",
    and one more type "class" which means "userdata" or "table", mainly used for builtin and
    inherited CCObject subclass
--]]
overload = setmetatable({}, {
                        __index = function (t,k)
                            local function reg(desc)
                                register(desc, k)
                            end
                            t[k] = reg
                            return reg
                        end
                    })