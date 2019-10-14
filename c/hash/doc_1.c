#include <stdio.h>

typedef unsigned int Index;

//tableSize为素数
Index Hash (const char *key, int tableSize)
{
	unsigned int HashVal = 0;
	while (*key != '\0') {
		printf("%c %u\n", *key, HashVal);
		HashVal = (HashVal << 5) + *key++;
	}
	return HashVal % tableSize;
}

int main(int argc, char const *argv[])
{

	Hash("abc", 107);
	const char *str = "abc";
	unsigned int x = 0;
	x = (x << 5) + *str++;
	printf("%u %c %s\n", x, *str, str);


	return 0;
}