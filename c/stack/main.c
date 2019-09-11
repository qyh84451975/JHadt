#include "Stack.h"
#include <stdio.h>

extern void _dump_stack(Stack *S);

int main(int argc, char const *argv[])
{

	Stack s;
	Init(&s);
	Push(&s, 1);
	Push(&s, 2);
	Push(&s, 3);
	Push(&s, 4);
	printf("s len1 = %d\n", Count(&s));
	printf("-----------------------------\n");
	_dump_stack(&s);
	printf("-----------------------------\n");
	int a;
	Pop(&s, &a);
	printf("a = %d\n", a);
	printf("s len2 = %d\n", Count(&s));
	printf("-----------------------------\n");
	_dump_stack(&s);
	printf("-----------------------------\n");

	return 0;
}