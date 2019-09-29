print("hello world!")
-- 使用xxd命令，查看luac.out的16进制显示
-- 1b4c 7561 5300 1993 0d0a 1a0a 0408 0408
-- 0x1b4c7561 魔术数 + 版本号(53=>5x16+3=83->0x53) 1993 1.0的发布年份 \r\n\x1a\n
-- 0878 5600 0000 0000 0000 0000 0000 2877
-- 整型8字节08,0x5678，本机是小端。

--[[Lua可以通过命令行工具luac，将Lua源码编译成二进制chunk，并且保存为luac.out。Lua解释器可以直接加载并执行chunk
.lua -> luac -> binary chunk(.out) -> lvm -> >_
--]]

-- Lua是以函数为单位编译的

--[[luac -l luac.out
-- 由编译器创建的主函数main
main <main.lua:0,0> (4 instructions at 0x7f8aa0c03360)
--固定参数数量、运行函数所必要的寄存器数量、upvalue数量、局部变量数量、常量数量、子函数数量
0+ params, 2 slots, 1 upvalue, 0 locals, 2 constants, 0 functions
	1	[1]	GETTABUP 	0 0 -1	; _ENV "print"
	2	[1]	LOADK    	1 -2	; "hello world!"
	3	[1]	CALL     	0 2 1
	4	[1]	RETURN   	0 1
指令列表里的每一条指令都包含指令序号、对应行号、操作码和操作数。分号后面是luac根据指令操作数生成的注释
--]]

-- Lua中数字：包括字节、C语言整型、size_t类型、Lua整数、Lua浮点数。

--[[ Lua中字符串：
1.NULL字符串，用0x00表示
2.对于长度<=253(0xfd)的字符串，用一个字节记录长度+1，然后说字节数组
3.长度>=254(0xfe)的字符串，第一个字节(0xff)，后面跟一个size_t记录长度+1，最后是字节数组

NULL [0]
n<=0xfd [n+1][bytes]
n>=0xfe [0xff][n+1][bytes]
]]

--[[Lua虚拟机使用定长指令集
每条指令4个字节(32bits)
操作码 			操作数
[低6bits Opcode] [高26bits Operand]
Lua5.3定义了47条指令大致分为：常量加载指令、运算符相关指令、循环和跳转指令、函数调用相关指令、表操作指令以及upvalue操作指令。

Lua虚拟机指令可分为4类对应4种编码模式:
1.iABC：可以携带A、B、C三个操作数，分别占8、9、9个bits
2.iABx：携带A和Bx两个操作数，分别占8、18个bits
3.iAsBx：携带A和sBx两个操作数，分别占用8、18个bits(只有此指令操作数会被解释成有符号整数)
4.iAx：携带一个操作数，占26个bits

		_____________________________________________________
iABC 	|	B:9		|	C:9 	|	A:8 	|	opcode:6 	|
		—————————————————————————————————————————————————————
iABx 	|	Bx:18 				|	A:8 	|	opcode:6 	|
		—————————————————————————————————————————————————————
iAsBx 	|	sBx:18				|	A:8 	|	opcode:6 	|
		—————————————————————————————————————————————————————
iAx 	|	Ax:9							|	opcode:6 	|
		—————————————————————————————————————————————————————
--]]

-- Lua8种数据类型
-- Lua5.3开始数字进一步分为浮点数和整数(整数是为了优化加到了虚拟机层面，Lua语言层没有提现)
print(type(nil)) 						-- nil
print(type(true))						-- boolean
print(type(3.14)) 						-- number
print(type("hello")) 					-- string
print(type({}))							-- table
print(type(coroutine.create(print)))	-- thread
print(type(io.stdin))					-- userdata

--[[ Lua栈索引
			_____________
			|	 		| <-5 (invalid)
			|-----------|
      -1->	|	  d		| <-4 (top)
			|-----------|
      -2->	|     c		| <-3
   			|-----------|
      -3->	|	  b		| <-2
			|-----------|
      -4->	| 	  a 	| <-1
   (相对索引)	|___________| (绝对索引)

设栈容量n, 栈顶索引top(0<top<=n)。[1, top]闭区间内索引有效，[1-n]闭区间索引为可接受索引
--]]

--[[ Lua运算符
1.算术运算符
+、-(减、一元取反)、*、/、//(整除)、%、^
^和字符串拼接符具有右结合性，其它二元运算符具有左结合性
100/10/2 == (100/10)/2
4^3^2 = 4^(3^2)
2.位运算符
&、|、~（二元异或、一元按位取反）、<<、>>
3.比较运算符
==、~=、>、>=、<、<=
4.逻辑运算符
and、or、not
--]]
print((5%2 == (5-((5//2)*2))))

--[[
luac -l -
local a, b, c, d,e; d=b
^D
main <stdin:0,0> (3 instructions at 0x7fbd21d00a40)
0+ params, 5 slots, 1 upvalue, 5 locals, 0 constants, 0 functions
	1	[1]	LOADNIL  	0 4
	2	[1]	MOVE     	3 1
	3	[1]	RETURN   	0 1

MOVE指令(iABC模式)把源寄存器（由操作数B指定）里的值移动到目标寄存器（由操作数A指定）里。
如果用R(N)表示寄存器N，MOVE指令可表示为：
R(A) := R(B)

------------------------
| B:1 | C: | A:3 | MOVE|
------------------------
B->a,b,c,d,e
A->a,b,c,b,e
由此还可看出，Lua中用A(8bits)来表示目标寄存器索引，所以Lua使用的局部变量不能超过255个。实际上Lua规定不多于200个。
--]]
--[[
local a1,b1,c1,d1,e1,f1,g1,h1,i1,j1,k1,l1,m1,n1,o1,p1,q1,r1,s1,t1
local a2,b2,c2,d2,e2,f2,g2,h2,i2,j2,k2,l2,m2,n2,o2,p2,q2,r2,s2,t2
local a3,b3,c3,d3,e3,f3,g3,h3,i3,j3,k3,l3,m3,n3,o3,p3,q3,r3,s3,t3
local a4,b4,c4,d4,e4,f4,g4,h4,i4,j4,k4,l4,m4,n4,o4,p4,q4,r4,s4,t4
local a5,b5,c5,d5,e5,f5,g5,h5,i5,j5,k5,l5,m5,n5,o5,p5,q5,r5,s5,t5
local a6,b6,c6,d6,e6,f6,g6,h6,i6,j6,k6,l6,m6,n6,o6,p6,q6,r6,s6,t6
local a7,b7,c7,d7,e7,f7,g7,h7,i7,j7,k7,l7,m7,n7,o7,p7,q7,r7,s7,t7
local a8,b8,c8,d8,e8,f8,g8,h8,i8,j8,k8,l8,m8,n8,o8,p8,q8,r8,s8,t8
local a9,b9,c9,d9,e9,f9,g9,h9,i9,j9,k9,l9,m9,n9,o9,p9,q9,r9,s9,t9
local a10,b10,c10,d10,e10,f10,g10,h10,i10,j10,k10,l10,m10,n10,o10,p10,q10,r10,s10,t10
local a11
--]]

--[[ 死循环
::B::
print('B')
goto B
--]]

--[[ Lua变量
1.局部变量：在函数内定义
2.Upvalue是直接或间接外围函数定义的局部变量
3.全局变量则是全局环境表的字段(隐藏的Upvalue，也就是_ENV进行访问)
--]]

print(getmetatable("foo"))
print(getmetatable(nil))
print(getmetatable(false))
print(getmetatable(100))
print(getmetatable({}))
print(getmetatable(print))

local t, mt = {}, {}
setmetatable(t, mt)
print(getmetatable(t) == mt)

debug.setmetatable(100, mt)
print(getmetatable(200) == mt)

local t1 = {11, 22, 33, 44}
local iter, _tt, _var = ipairs(t1)
while true do
	local i, v = iter(_tt, _var)
	_var = _var + 1
	if i == nil then break end
	print(i, v)
end
for k, v in next, t1 do
	print(k, v)
end

print("hello,\z
	world!")

print(package.loaded["test"])
require "test"
print(package.loaded["test"])

for k, v in pairs(package.searchers) do
	print(k, v)
end

print(package.path)
print(package.searchpath)
print(package.config)

require "test1"

local main = coroutine.running()
-- for k, v in pairs(coroutine) do
-- 	print(k, v)
-- end

local co
co = coroutine.create(function()
	print(coroutine.status(co))
	coroutine.resume(coroutine.create(function()
		print(coroutine.status(co))
	end))
end)
print(coroutine.status(co))
coroutine.resume(co)
print(coroutine.status(co))


--[[
--------------------|
|		表			|
|-----------|-------|
|	数组		|	记录	|
|			|		|
|-------|   |		|
|	序列	|	|		|
|		|	|		|
|		|	|		|
--------------------|
--]]

--[[Lua执行流程
luaL_newstate
lua_newstate(l_alloc, NULL)
(LG*)l_alloc()
luaD_rawrunprotected(L, f_luaopen, NULL)
f_luaopen()
stack_init(L)
--]]








