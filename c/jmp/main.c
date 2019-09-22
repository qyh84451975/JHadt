/**
 * 利用jmp实现c语言的异常处理
 */

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

#define MY_THROW(c) longjmp((c)->b, 1)
#define MY_TRY(c, a) if (setjmp((c)->b) == 0) {a}
#define my_jmpbuf jmp_buf

struct my_longjmp {
	my_jmpbuf b;
	volatile int status; // error code
};

void throw_f(struct my_longjmp *lj)
{
	lj->status = 1000;
	MY_THROW(lj);
}

int main(int argc, char const *argv[])
{

	struct my_longjmp lj;
	lj.status = 0;

	MY_TRY(&lj, throw_f(&lj););
	printf("after try %d\n", (&lj)->status);

	return 0;
}


#ifdef TEST1

jmp_buf jb;

void f1()
{
	printf("call f1() began.\n");
	if (0) {

	} else {
		longjmp(jb, 1);
	}
	printf("call f1() ended.");
}

void f2()
{
	printf("call f2() began.\n");
	if (1) {

	} else {
		longjmp(jb, 2);
	}
	printf("call f2() ended.\n");
}


int main(int argc, char const *argv[])
{
	// longjmp(jb, r)之后，携带着r，跳转到setjmp之后的语句。
	int r = setjmp(jb);
	printf("rr = %d\n", r);
	if (r == 0) {
		f1();
		f2();
	} else if (r == 1) {
		printf("f1 error\n");
		exit(1);
	} else if (r == 2) {
		printf("f2 error\n");
		exit(2);
	}

	return 0;
}
#endif

#ifdef TEST

// jmp_buf 是个int数组 int jmp_buf[48];
jmp_buf jb;
// c语言都是先声明之后才能调用。注意调用顺序以及声明顺序。
void c() {
	printf("call c\n");
	longjmp(jb, 1);
}
void b() {
	c();
	printf("call b\n");
}
void a() {
	b();
	printf("call a\n");
}

int main(int argc, char const *argv[])
{
	// setjmp用来保存AR(过程活动记录（Active Record）)到jb中
	// longjmp用于设置当前AR为jb，并跳转到调用setjmp之后的第一个语句处。调用结果相当于回到了setjmp刚执行完毕，并且修改了setjmp的返回值
	// setjmp第一次调用总是返回0，通过longjmp(jb,r)跳转后，其返回值总是被修改为r并且r!=0
	if (setjmp(jb) == 0) {
		a();
	}
	printf("call after a()\n");


	return 0;
}

#endif