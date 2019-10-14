#include "BinHeap.h"
#include <stdlib.h>

#define MinPQSize (10);
#define MinData (-32767)

/**
 * 1. 结构性质：任意节点i,其左子节点为2i,右子节点为2i+1,且树是从左往右依次填充。
 * 2. 堆序性质：任意节点的左右子节点都大于父节点
 */

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	if (MaxElements < MinPQSize)
		return NULL;
	H = malloc(sizeof(struct HeapStruct));
	H->Elements = malloc(sizeof(ElementType) * (MaxElements+1));
	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = MinData;
	return H;
}

void Destroy(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}

void MakeEmpty(PriorityQueue H)
{
	H->Size = 0;
}

void Insert(PriorityQueue H, ElementType X)
{
	int i;
	if (IsFull(H)) return;
	// 不停与父节点值进行交换
	for (i = ++H->Size; H->Elements[i/2]>X; i/=2)
		H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = X;
}

ElementType DelteMin(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;
	if (IsEmpty(H)) {
		return H->Elements[0];
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];
	for (i = 1; i * 2 <= H->Size; i = Child) {
		Child = i * 2;
		if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;
		if (LastElement > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

ElementType FindMin(PriorityQueue H)
{
	return H->Elements[0];
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}
