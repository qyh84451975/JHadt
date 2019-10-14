/**
 * 不安全宏参数的副作用
 */

#include <stdio.h>
#include <complex.h>
#include <math.h>

#define ABS(x) (((x) < 0) ? -(x) : (x))

void func (int n)
{
	int a = ABS(++n);
	printf("a = %d\n", a);
}

// 方案1.
void func1 (int n)
{
	n++;
	int a = ABS(n);
	printf("use safe 1 a = %d\n", a);
}

// 方案2.
// 此方法截断了所有超过int宽度的类型
static inline int iabs (int x)
{
	return (((x) < 0) ? -(x) : (x));
}
void func2 (int n)
{
	int a = iabs(++n);
	printf("use safe 2 a = %d\n", a);
}

// 方案3.
static inline long long llabs (long long v)
{
	return v < 0 ? -v : v;
}
static inline long labs (long v)
{
	return v < 0 ? -v : v;
}
static inline int iabs1 (int v)
{
	return v < 0 ? -v : v;
}
static inline int sabs (short v)
{
	return v < 0 ? -v : v;
}
static inline int scabs (signed char v)
{
	return v < 0 ? -v : v;
}
static inline float fabsf1 (float v)
{
	return v < 0 ? -v : v;
}
// C11 新标准_Generic泛型编程，根据类型匹配表达式。此处是作为函数调用
#define ABS1(v) _Generic(v, signed char : scabs,\
	short : sabs, \
	int : iabs, \
	long : labs, \
	long long : llabs, \
	float : fabsf1)(v)

void func3 (int n)
{
	int a = ABS1(++n);
	printf("use safe 3 a = %d\n", a);
}

// 另外assert宏依赖NDEBUG宏，当定义了NDEBUG时，assert宏表示((void)0)
// 因此如果assert宏中有类似的assert(i++>0);的表达式，会导致i不求值。

int main(int argc, char const *argv[])
{
	func(1);
	func1(1);
	func2(1);
	func3(1);
	printf("%f\n", ABS1(1.f));




	return 0;
}
