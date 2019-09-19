#include <stdio.h>

void print_hex(const char * desc, int d)
{
	printf("%s: 0x%x\n", desc, d);
}

int main(int argc, char const *argv[])
{

	print_hex("BIT_ISCOLLECTABLE", (1 << 6));

	return 0;
}