print("not found some file.")

local mt = {}
mt.__index = function(t, k)
	return 2
end
local t = {a=1}
setmetatable(t, mt)
print(t.a, t.b)



local ok, ret = xpcall(function()
	error({err="unable eeee"})
end, function(errdata)
	print(errdata.err)
end)