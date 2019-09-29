/**
 * Lua 中的字符串hash存储
 */

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "structs.h"

#define luai_makeseed() cast(unsigned int, time(NULL))

#define addbuff(b, p, e) \
	{ size_t t = cast(size_t, e); \
	  memcpy(b + p, &t, sizeof(t)); p += sizeof(t); }

// 利用地址的分配的随机性，产生种子
unsigned int makeseed ()
{
	char buff[2 * sizeof(size_t)];
	unsigned int h = luai_makeseed();
	int p = 0;
	addbuff(buff, p, &h);
	addbuff(buff, p, nilobject);
	return l_hash(buff, p, h);
}

// 异或性质: A ^ B ^ B = A
unsigned int l_hash (const char *str, size_t len, unsigned int seed)
{
	unsigned int h = seed ^ cast(unsigned int, len);
	size_t step = (len >> 5) + 1;
	// 当字符串不大于63个字符时，进行逐字节计算
	// 否则，进行跳跃式计算，以提高计算效率
	for (; len >= step; len -= step) {
		h ^= ((h << 5) + (h >> 2) + cast(byte, str[len - 1]));
	}
	return h;
}

struct TestA {
	void *p;
	int b;
};
typedef struct InitTest {
	struct TestA a;
	// void *p;
	int b;
	double c;
} InitTest;

#ifdef TEST_4

int main(int argc, char const *argv[])
{
	// 结构体会按顺序初始化，如果初始化的为结构体，必须类型匹配。
	// 如NULL初始化了struct TestA 的void *p
	InitTest it = {NULL, 1, 0.0};
	printf("it a %p\n", it.a.p);
	printf("it b %d\n", it.b);
	printf("it c %f\n", it.c);

	printf("nilobject: %p\n", nilobject);

	const char * arr[] = {
		"hello", "world", "best", "guy", "ervery", "body", "xzyabc"
	};

	for (int i = 0; i < 7; i++) {
		printf("%s hash = %u\n", arr[i], l_hash(arr[i], strlen(arr[i]), makeseed()));
	}

	return 0;
}

#endif
