
#include <stdio.h>
#include <stdlib.h>
#include "LinearList.h"

int main(int argc, char const *argv[])
{

	SqList l1;
	Init_seq(&l1);
	Insert_seq(&l1, 1, 5);
	Insert_seq(&l1, 2, 6);
	Insert_seq(&l1, 3, 7);
	Insert_seq(&l1, 4, 8);
	int a1;
	GetElem_seq(l1, 2, &a1);
	printf("a1 = %d\n", a1);
	int b1;
	Delete_seq(&l1, 2, &b1);
	printf("b1 = %d\n", b1);
	int c1;
	GetElem_seq(l1, 2, &c1);
	printf("c1 = %d\n", c1);
	printf("l1 len = %d\n", l1.length);

	LinkList l2 = (LinkList)malloc(sizeof(Node));
	Init_1(&l2);
	Insert_1(&l2, 1, 5);
	Insert_1(&l2, 2, 6);
	Insert_1(&l2, 3, 7);
	Insert_1(&l2, 4, 8);
	int a2;
	GetElem_1(l2, 2, &a2);
	printf("a2 = %d\n", a2);
	int b2;
	Delete_1(&l2, 2, &b2);
	printf("b2 = %d\n", b2);
	int c2;
	GetElem_1(l2, 2, &c2);
	printf("c2 = %d\n", c2);
	free(l2);

	return 0;
}