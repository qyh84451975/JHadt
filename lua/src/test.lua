print("hello world!")
local file = io.open("test.lua", "a")
file:write("-- 添加一段注释\n")
file:close()
