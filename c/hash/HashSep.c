// 分离链接散列

#include "HashSep.h"
#include "../common.h"

#include <stdlib.h>

#define MinTableSize (10)
typedef unsigned int Index;

Index Hash (ElementType Key, int TableSize)
{
	return Key % TableSize;
}

struct ListNode {
	ElementType Element;
	Position Next;
};

typedef Position List;

// hash表的大小TableSize
// TheList:是一个数组，此数组保存了TableSize个List指针
struct HashTbl {
	int TableSize;
	List *TheList;
};

static int NextPrime (int N)
{
	int i;
	if (N % 2 == 0)
		N++;
	for (;;N+=2) {
		for (i = 3; i * i <= N; i += 2)
			if (N % i == 0)
				goto ContOuter;
		return N;
		ContOuter: ;
	}
}

HashTable InitializeTable (int TableSize)
{
	HashTable H;
	int i;
	if (TableSize < MinTableSize) {
		return NULL;
	}
	H = malloc(sizeof(struct HashTbl));
	H->TableSize = NextPrime( TableSize );
	H->TheList = malloc(sizeof(List) * H->TableSize);
	for (i = 0; i < H->TableSize; i++) {
		H->TheList[i] = malloc(sizeof(struct ListNode));
		H->TheList[i]->Next = NULL;
	}
	return H;
}

void DestroyTable (HashTable H)
{
	int i;
	for (i = 0; i < H->TableSize; i++) {
		Position P = H->TheList[i];
		Position Tmp;
		while (P != NULL) {
			Tmp = P->Next;
			free(P);
			P = Tmp;
		}
	}
	free(H->TheList);
	free(H);
}

Position Find (HashTable H, ElementType Key)
{
	Position P;
	List L;
	L = H->TheList[Hash(Key, H->TableSize)];
	P = L->Next;
	while (P != NULL && P->Element != Key)
		P = P->Next;
	return P;
}

void Insert (HashTable H, ElementType Key)
{
	Position pos, cell;
	List L;
	pos = Find(H, Key);
	if (pos == NULL) {
		cell = malloc(sizeof(struct ListNode));
		// 不管有没有hash冲突，都存在对应hash位置上的链表中
		L = H->TheList[Hash(Key, H->TableSize)];
		cell->Next = L->Next;
		cell->Element = Key;
		L->Next = cell;
	}
}

int main(int argc, char const *argv[])
{
	HashTable H = InitializeTable(10);
	printf("H->TableSize = %d\n", H->TableSize);

	return 0;
}
