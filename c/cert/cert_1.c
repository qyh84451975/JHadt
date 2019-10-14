/**
 * C 支持通用字符名称，表示不在基本字符子集的字符。
 * \Unnnnnnnn、\unnnn(0000nnnn)
 */

/*
#define assign_w(uc1, uc2, val) uc1##uc2 = val

void func_w(void)
{
	int \u0401;
	assign_w(\u04, 01, 4);
}
*/

#include <stdio.h>

#define assign(uc, val) (uc) = (val)

void func (void)
{
	int \u0401;
	assign(\u0401, 1);
}

int main(int argc, char const *argv[])
{
	func();
	return 0;
}