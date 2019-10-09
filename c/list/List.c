#include "List.h"
#include "../common.h"

#include <stdlib.h>

struct Node {
	// 存储数据
	ElementType Element;
	// 指向链表下个元素
	Position Next;
};

// 创建一个空表，头指针L并不作存储用。
List MakeEmpty (List L)
{
	if (L != NULL) {
		DeleteList(L);
		return L;
	}
	L = malloc(sizeof(struct Node));
	if (L == NULL)
		writeerr("fail to malloc memeroy.");
	L->Next = NULL;
	return L;
}

// 如果是空列表，头元素和尾元素相同
int IsEmpty (List L)
{
	return L->Next == NULL;
}

int IsLast (List L, Position P)
{
	UNUSED(L);
	return P->Next == NULL;
}

Position Find (List L, ElementType X)
{
	Position pos;
	pos = L->Next;
	while (pos != NULL && pos->Element != X)
		pos = pos->Next;
	return pos;
}

Position FindPrevious (List L, ElementType X)
{
	Position pos;
	pos = L;
	// 返回的位置始终指向L的最后一个元素
	while (pos->Next != NULL && pos->Next->Element != X)
		pos = pos->Next;
	return pos;
}

void Delete (List L, ElementType X)
{
	Position previous = FindPrevious(L, X);
	if (!IsLast(L, previous)) {
		Position temp = previous->Next;
		previous->Next = temp->Next;
		free(temp);
	}
}

void Insert (List L, Position P, ElementType X)
{
	UNUSED(L);
	PtrToNode newNode = malloc(sizeof(struct Node));
	if (newNode == NULL)
		writeerr("fail to malloc memeroy.");
	newNode->Element = X;
	newNode->Next = P->Next;
	P->Next = newNode;
}

// 删除之后，会剩余一个sturct Node大小的空表
void DeleteList (List L)
{
	Position pos, temp;
	pos = L->Next;
	L->Next = NULL;
	while (pos != NULL) {
		temp = pos->Next;
		free(pos);
		pos = temp;
	}
}

// 头指针
Position Header (List L)
{
	return L;
}

// 第一个正式存储元素的指针
Position First (List L)
{
	return L->Next;
}

Position Advance (Position P)
{
	return P->Next;
}

ElementType Retrieve (Position P)
{
	return P->Element;
}

Position Next (Position P, List L)
{
	UNUSED(L);
	return P->Next;
}

static void dump_list (List L)
{
	Position pos = L->Next;
	while (pos != NULL) {
		printf("%d\n", pos->Element);
		pos = pos->Next;
	}
}

static void print_lots (List L, List P)
{
	int counter;
	Position Lpos, Ppos;
	Lpos = First(L);
	Ppos = First(P);
	counter = 1;
	while (Lpos != NULL && Ppos != NULL) {
		if (Ppos->Element == counter++) {
			printf("%d\n", Lpos->Element);
			Ppos = Next(Ppos, P);
		}
		Lpos = Next(Lpos, L);
	}
}

int main(int argc, char const *argv[])
{
	List L = NULL;
	L = MakeEmpty(L);
	// 可以有个push_back向列表末尾添加一个元素
	Insert(L, L, 1);
	Insert(L, L->Next, 2);
	Insert(L, L->Next->Next, 3);
	Insert(L, L->Next->Next->Next, 4);
	dump_list(L);
	printf("\n");
	Delete(L, 3);
	dump_list(L);

	List P = NULL;
	P = MakeEmpty(P);
	Insert(P, P, 1);
	Insert(P, P->Next, 3);
	printf("\n");
	print_lots(L, P);


	return 0;
}
