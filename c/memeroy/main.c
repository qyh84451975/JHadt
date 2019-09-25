/**
 * 内存分配需要包含头文件<stdlib.h>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * void * malloc(size_t, size)
 *
 * 该函数用于从堆中分配内存空间，内存分配大小为 size。如果内存分配成功，则返回首地址；如果内存分配失败，则返回 NULL。
 */

/**
 * void * calloc(size_t num, size_t size)
 *
 * 该函数用于从堆中分配 num 个相邻的内存单元，每个内存单元的大小为 size。如果内存分配成功则返回第一个内存单元的首地址；否则内存分配失败，则返回 NULL。
 * 从功能上看，calloc 函数与语句“malloc（num*size）”的效果极其相似。但不同的是，在使用 calloc 函数分配内存时，会将内存内容初始化为 0。
 */

/**
 * void * realloc(void *ptr, size_t size)
 *
 * 该函数用于更改已经配置的内存空间，它同样是从堆中分配内存的。当程序需要扩大一块内存空间时，
 * realloc 函数试图直接从堆上当前内存段后面的字节中获得更多的内存空间，即它将首先判断当前的指针是否有足够的连续存储空间，
 * 如果有，则扩大 ptr 指向的地址，并且将 ptr 返回（返回原指针）；如果当前内存段后面的空闲字节不够，那么将先按照 size
 * 指定的大小分配空间（使用堆上第一个能够满足这一要求的内存块），并将原有数据从头到尾拷贝到新分配的内存区域，然后释放原来
 * ptr 所指内存区域，同时返回新分配的内存区域的首地址，即重新分配存储器块的地址。
 *
 * 需要注意的是，参数 ptr 为指向先前由 malloc、calloc 与 realloc 函数所返回的内存指针，而参数 size 为新分配的内存大小，其值可比原内存大或小。其中：
 * 如果 size 值比原分配的内存空间小，内存内容不会改变（即新内存保持原内存的内容），且返回的指针为原来内存的首地址（即 ptr）。
 * 如果 size 值比原分配的内存空间大，则 realloc 不一定会返回原来的指针，原内存的内容保持不变，但新多出的内存则设为初始值。
 * 最后，如果内存分配成功，则返回首地址；如果内存分配失败，则返回 NULL。
 */

/**
 * void * alloca(size_t size)
 *
 * 相对与 malloc、calloc 与 realloc 函数，函数 alloca 是从栈中分配内存空间，内存分配大小为 size。
 * 如果内存分配成功，则返回首地址；如果内存分配失败，则返回 NULL。也正因为函数 alloca 是从栈中分配内存空间，因此它会自动释放内存空间，而无需手动释放。
 */

/**
 * void * aligned_alloc(size_t alignment, size_t size)
 *
 * 该函数属于 C11 标准提供的新函数，用于边界对齐的动态内存分配
 */

/**
 * #include <string.h>
 * 内存拷贝函数
 * void * memcpy(void *destin, void *source, unsigned n)
 * 从源内存地址的起始位置开始拷贝若干个字节到目标内存地址中，即从源source中拷贝n个字节到目标destin中
 * 该函数返回一个指向目标存储区destin的指针
 */

typedef struct T {
	int a;
	double b;
	void *c;
} T;

#include <time.h>

int main(int argc, char const *argv[])
{
	T t1;
	t1.a = 0;
	t1.b = 0;
	t1.c = NULL;
	char buff[sizeof(size_t)];
	size_t t = (size_t) (&t1);
	printf("%lu\n", t);
	printf("%p\n", &t1);
	printf("%lu\n", &t1);
	printf("%lu\n", sizeof(t));
	int p = 0;
	memcpy(buff + p, &t, sizeof(t));
	p += sizeof(t);

	unsigned int h = (unsigned int) (time(NULL));

	unsigned int hh = h ^ ((unsigned int) p);
	size_t step = (p >> 5) + 1;
	for (; p >= step; p -= step)
		hh ^= ((hh<<5) + (hh>>2) + ((unsigned char) (buff[p-1])));

	printf("%d\n", hh);


	return 0;
}