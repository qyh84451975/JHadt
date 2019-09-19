#ifndef __LOPCODES__
#define __LOPCODES__

#include "llimits.h"

/*
 * Lua虚拟机指令占用4个字节。其中低6位用于操作码，高26位用于操作数。
 *
 *Lua虚拟机指令可分为4类对应4种编码模式:
 *1.iABC：可以携带A、B、C三个操作数，分别占8、9、9个bits
 *2.iABx：携带A和Bx两个操作数，分别占8、18个bits
 *3.iAsBx：携带A和sBx两个操作数，分别占用8、18个bits(只有此指令操作数会被解释成有符号整数)
 *4.iAx：携带一个操作数，占26个bits
		_____________________________________________________
 iABC 	|	B:9		|	C:9 	|	A:8 	|	opcode:6 	|
		—————————————————————————————————————————————————————
 iABx 	|	Bx:18 				|	A:8 	|	opcode:6 	|
		—————————————————————————————————————————————————————
 iAsBx |	sBx:18				|	A:8 	|	opcode:6 	|
		—————————————————————————————————————————————————————
 iAx 	|	Ax:26							|	opcode:6 	|
		—————————————————————————————————————————————————————
在总计47条指令中，有39条使用iABC模式。
其余8条指令中，有3条使用iABx指令，4条使用iAsBx模式，1条使用iAx格式（其实用来扩展其它操作数的）”
 */
// 指令模式
enum OpMode {iABC, iABx, iAsBx, iAx};

// 其中sBx为有符号整数，Lua虚拟机采用偏移二进制码(Excess-K)的编码模式，将有符号整数编码成bit序列。
// sBx被解释成无符号整数时它的值是x,那么解释成有符号整数时它的值就是x-K。K取sBx所能表示的最大无符号整数值的一半。
#define SIZE_C 	9
#define SIZE_B 	9
#define SIZE_Bx	(SIZE_C + SIZE_B)
#define SIZE_A  8
#define SIZE_Ax (SIZE_C + SIZE_B + SIZE_A)
#define SIZE_OP 6
#define POS_OP 	0
#define POS_A 	(POS_OP +SIZE_OP)
#define POS_C 	(SIZE_A + POS_A)
#define POS_B 	(SIZE_C + POS_C)
#define POS_Bx 	POS_C
#define POS_Ax 	POS_A

#if SIZE_Bx < LUAI_BITSINT-1
#define MAXARG_Bx ((1<<SIZE_Bx)-1)
#define MAXARG_sBx (MAXARG_Bx >> 1)
#else
#define MAXARG_Bx MAX_INT
#define MAXARG_sBx MAX_INT
#endif

#if SIZE_Bx < LUAI_BITSINT-1
#define MAXARG_Ax ((1<<SIZE_Ax)-1)
#else
#define MAXARG_Ax MAX_INT
#endif

#define MAXARG_A ((1<<SIZE_A)-1)
#define MAXARG_B ((1<<SIZE_B)-1)
#define MAXARG_C ((1<<SIZE_C)-1)

// 从位置p开始创建n个1
#define MASK1(n, p) ((~((~(Instruction)0)<<(n)))<<(p))
// 从位置p开始创建n个0
#define MASK0(n, p) (~(MASK1(n, p)))
#define GET_OPCODE(i) (cast(OpCode, ((i)>>POS_OP) & MASK1(SIZE_OP, 0)))
#define SET_OPCODE(i, o) ((i) = (((i)&MASK0(SIZE_OP, POS_OP)) | ((cast(Instruction, o)<<POS_OP) & MASK1(SIZE_OP, POS_OP))))
#define getarg(i, pos, size) (cast(int, ((i)>>pos) & MASK1(size, 0)))
#define setarg(i, v, pos, size) ((i) = (((i) & MASK0(size, pos)) | ((cast(Instruction, v)<<pos) & MASK1(size, pos))))

#define GETARG_A(i)	getarg(i, POS_A, SIZE_A)
#define SETARG_A(i,v)	setarg(i, v, POS_A, SIZE_A)

#define GETARG_B(i)	getarg(i, POS_B, SIZE_B)
#define SETARG_B(i,v)	setarg(i, v, POS_B, SIZE_B)

#define GETARG_C(i)	getarg(i, POS_C, SIZE_C)
#define SETARG_C(i,v)	setarg(i, v, POS_C, SIZE_C)

#define GETARG_Bx(i)	getarg(i, POS_Bx, SIZE_Bx)
#define SETARG_Bx(i,v)	setarg(i, v, POS_Bx, SIZE_Bx)

#define GETARG_Ax(i)	getarg(i, POS_Ax, SIZE_Ax)
#define SETARG_Ax(i,v)	setarg(i, v, POS_Ax, SIZE_Ax)

#define GETARG_sBx(i)	(GETARG_Bx(i)-MAXARG_sBx)
#define SETARG_sBx(i,b)	SETARG_Bx((i),cast(unsigned int, (b)+MAXARG_sBx))

// 创建一个ABC指令
#define CREATE_ABC(o,a,b,c) ((cast(Instruction, o)<<POS_OP) \
	| (cast(Instruction, a) << POS_A) \
	| (cast(Instruction, b) << POS_B) \
	| (cast(Instruction, c) << POS_C))
// 创建一个ABx指令
#define CREATE_ABx(o,a,bc)	((cast(Instruction, o)<<POS_OP) \
			| (cast(Instruction, a)<<POS_A) \
			| (cast(Instruction, bc)<<POS_Bx))
// 创建一个Ax指令
#define CREATE_Ax(o,a)		((cast(Instruction, o)<<POS_OP) \
			| (cast(Instruction, a)<<POS_Ax))

// B的低8位表示操作数，高1位如果为1表示常量，0表示寄存器
// 取高1位
#define BITRK (1 << (SIZE_B - 1))
#define ISK(x) ((x) & BITRK)
// 获取常量索引
#define INDEXK(r) ((int)(r) & ~BITRK)

// 指令集
typedef enum {
	OP_MOVE, 			// A B R(A) := R(B)
	OP_LOADK, 			// A Bx R(A) := Kst(Bx) Kst(常量表访问)
	OP_LOADKX, 			// A R(A) := Kst(extra arg)
	OP_LOADBOOL, 		// A B C R(A) := (Bool) B; if (C) pc++
	OP_LOADNIL, 		// A B R(A), R(A+1), ..., R(A+B) := nil
	OP_GETUPVAL, 		// A B R(A) := UpValue[B]
	OP_GETTABUP, 		// A B C R(A) := UpValue[B][RK(C)]
	OP_GETTABLE, 		// A B C R(A) := R(B)[RK(C)]
	OP_SETTABUP, 		// A B C UpValue[A][RK(B)] := RK(C)
	OP_SETUPVAL, 		// A B UpValue[B] := R(A)
	OP_SETTABLE, 		// A B C R(A)[RK(B)] := RK(C)
	OP_NEWTABLE, 		// A B C R(A) := {} (size = B,C)
	OP_SELF, 			// A B C R(A+1) := R(B); R(A) := R(B)[RK(C)]
	OP_ADD, 			// A B C R(A) := RK(B) + RK(C)
	OP_SUB, 			// A B C R(A) := RK(B) - RK(C)
	OP_MUL, 			// A B C R(A) := RK(B) * RK(C)
	OP_MOD, 			// A B C R(A) := RK(B) % RK(C)
	OP_POW, 			// A B C R(A) := RK(B) ^ RK(C)
	OP_DIV, 			// A B C R(A) := RK(B) / RK(C)
	OP_IDIV, 			// A B C R(A) := RK(B) // RK(C)
	OP_BAND, 			// A B C R(A) := RK(B) & RK(C)
	OP_BOR, 			// A B C R(A) := RK(B) | RK(C)
	OP_BXOR, 			// A B C R(A) := RK(B) ~ RK(C)
	OP_SHL, 			// A B C R(A) := RK(B) << RK(C)
	OP_SHR, 			// A B C R(A) := RK(B) >> RK(C)
	OP_UNM, 			// A B R(A) := -R(B)
	OP_BNOT, 			// A B R(A) := ~R(B)
	OP_NOT, 			// A B R(A) := not R(B)
	OP_LEN, 			// A B R(A) := length of R(B)
	OP_CONCAT, 			// A B C R(A) := R(B) .. ... .. R(C)
	OP_JMP, 			// A sBx pc+=sBx; if (A) close all upvalues >= R(A-1)
	OP_EQ, 				// A B C if ((RK(B) == RK(C)) ~= A) then pc++
	OP_LT, 				// A B C if ((RK(B) < RK(C)) ~= A) then pc++
	OP_LE, 				// A B C if ((RK(B) <= RK(C)) ~= A) then pc++
	OP_TEST, 			// A C if not (R(A) <=> C) then pc++
	OP_TESTSET, 		// A B C if (R(B) <=> C) then R(A) := R(B) else pc++
	OP_CALL,			// A B C R(A), ..., R(A+C-2) := R(A)(R(A+1), ..., R(A+B-1))
	OP_TAILCALL, 		// A B C return R(A)(R(A+1), ..., R(A+B-1))
	OP_RETURN, 			// A B return R(A), ..., R(A+B-2)
	OP_FORLOOP, 		// A sBx R(A) += R(A+2); if R(A) <?= R(A+1) then {pc+=sBx; R(A+3)=R(A)}
	OP_FORPREP, 		// A sBx R(A)==R(A+2); pc+=sBx
	OP_TFORCALL, 		// A C R(A+3), ..., R(A+2+C) := R(A)R(A+1), R(A+2)
	OP_TFORLOOP, 		// A sBx if R(A+1) ~= nil then {R(A)=R(A+1); pc+=sBx}
	OP_SETLIST, 		// A B C R(A)[(C-1)*FPF+i] := R(A+i), 1 <= i <= B
	OP_CLOSURE, 		// A Bx R(A) := closure(KPROTO[Bx])
	OP_VARARG, 			// A B R(A), R(A+1), ..., R(A+B-2) = vararg
	OP_EXTRAARG, 		// Ax extra (larger) argument for previous opcode
} OpCode;

#define NUM_OPCODES (cast(int, OP_EXTRAARG) + 1)

/*
 * Lua中，每条指令可以携带1-3个操作数。其中操作数A主要用来表示目标寄存器索引
 * 其他操作数按照其表示的信息，可以大致分为四种类型：OpArgN、OpArgU、OpArgR、OpArgK
 * OpArgN:不表示任何信息。如：MOVE指令(iABC)只使用A和B，不使用C(OpArgN)
 * OpArgR:在iABC模式下表示寄存器索引，在iAsBx模式下表示跳转偏移。
 * OpArgK:类型的操作数表示常量表索引或者寄存器索引
 */
enum OpArgMask {OpArgN, OpArgU, OpArgR, OpArgK};

LUAI_DDEC const lu_byte luaP_opmodes[NUM_OPCODES];
LUAI_DDEC const char *const luaP_opnames[NUM_OPCODES+1];

/*
 * bits 0-1: op mode
 * bits 2-3: C arg mode
 * bits 4-5: B arg mode
 * bit 6: instruction set register A
 * bit 7: operator is a test (next instruction must be a jump)
 */
#define getOpMode(m) (cast(enum OpMode, luaP_opmodes[m] & 3))
#define getBMode(m) (cast(enum OpArgMask, (luaP_opmodes[m] >> 4) & 3))
#define getCMode(m)	(cast(enum OpArgMask, (luaP_opmodes[m] >> 2) & 3))
#define testAMode(m)	(luaP_opmodes[m] & (1 << 6))
#define testTMode(m)	(luaP_opmodes[m] & (1 << 7))
// 测试打印指令名称
// #define getOpName(m) (cast(const char *, luaP_opnames[m]))



#endif /* __LOPCODES__ */