#include <stdio.h>
#include "common.h"

/**
 * 浮点型字节编码
 * eeeeexxx:当eeeee为0时表示xxx，否则表示(1xxx) * 2 ^ (eeeee - 1)
 */
// 编码
int int2fb(unsigned int x)
{
	int e = 0;
	//00000111
	if (x < 8) return x;
	while (x >= (8 << 4)) {
		// 直接移位会导致低4位丢失(向下取整)
		// 补上需要移位的位数(向上取整)
		x = (x + 0xf) >> 4;
		e += 4;
	}
	while (x >= (8 << 1)) {
		x = (x + 1) >> 1;
		e++;
	}
	// 如果整数是4字节，最多移动也不会超过32位(即 2^5)，合成之后的字节小于255
	return ((e + 1) << 3) | (cast_int(x) - 8);
}
// 解码
int fb2int(int x)
{
	return (x < 8) ? x : ((x & 7) + 8) << ((x >> 3) - 1);
}

#ifdef TEST_1

int main(int argc, char const *argv[])
{
	/**
	 * 在Lua中使用此算法计算表得hash部分和数组部分的大小。
	 * 1.在表构造的时候会传入数组部分大小na和hash部分大小ha，此大小会通过int2fb编码，编码过后的大小会在操作数范围内。
	 * 2.在真正申请内存的时候，会通过fb2int解码，得到的数值不小于na和ha。
	 */
	int i;
	for (i = 0; i < 1000000; i++) {
		int i2fb = int2fb(i);
		int fb2i = fb2int(i2fb);
		printf("%d -> %d -> %d\n", i, i2fb, fb2i);
	}

	return 0;
}

#endif /* TEST */
