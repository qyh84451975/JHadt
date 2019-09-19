#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double dvalue;
	int ivalue;
} showal;

/**
 * 在结构中可以使用联合，而不指出名字，这样可以直接使用联合的成员，就好像他们是结构中的成员一样
 */
struct
{
	char code;
	union {
		char chid[12];
		int numid;
	};
	char *name;
} morx;

/**
 * gun c允许声明长度为0的数组，用于创建变长结构。只有0长度数组是结构体的最后一个成员时，才有意义。
 */
typedef struct
{
	int size;
	char string[0];
} vlen;

// vlen initvlen = {4, {'a', 'b', 'c', 'd'}};

int main(int argc, char const *argv[])
{

	printf("__alignof__(char)=%lu\n", __alignof__(char));
	printf("__alignof__(short)=%lu\n", __alignof__(short));
	printf("__alignof__(int)=%lu\n", __alignof__(int));
	printf("__alignof__(long)=%lu\n", __alignof__(long));
	printf("__alignof__(long long)=%lu\n", __alignof__(long long));
	printf("__alignof__(float)=%lu\n",__alignof__(float));
	printf("__alignof__(double)=%lu\n",__alignof__(double));
	printf("__alignof__(showal)=%lu\n",__alignof__(showal));
	printf("__alignof__(morx)=%lu\n",__alignof__(morx));

	printf("sizeof(morx)=%lu\n",sizeof(morx));

	int i;
	int count = 22;
	char letter = 'a';
	printf("malloc size = %lu\n", sizeof(vlen) + count);
	vlen *line = (vlen *)malloc(sizeof(vlen) + count);
	line->size = count;
	for (i = 0; i < count; i++) {
		line->string[i] = letter++;
	}
	printf("sizeof(vlen)=%lu\n", sizeof(vlen));
	for (i = 0; i < line->size; i++) {
		printf("%c ", line->string[i]);
	}
	printf("\n");

	return 0;
}