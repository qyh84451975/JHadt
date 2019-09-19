#include <stdio.h>

union dparts {
	unsigned char byte[8];
	double dbl;
};

int main(int argc, char const *argv[])
{
	// 数据项value和union中成员类型相同，可以将该数据项转换为联合。
	// 此处因为dparts有double，所以可以转换，并可以访问每个字节
	int i;
	double value = 3.14158;
	for (i = 0; i < 8; i++) {
		printf("%02X", ((union dparts)value).byte[i]);
	}
	printf("\n");

	// 由于union是构造器，并不会创建左值
	// (union dparts)value.dbl = 1.2 //error

	return 0;
}