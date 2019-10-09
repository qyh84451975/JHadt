#include "ArrayQueue.h"
#include "../common.h"

#include <stdlib.h>

#define MinQueueSize (5)

struct QueueRecord {
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;
};

int IsEmpty (Queue Q)
{
	return Q->Size == 0;
}

int IsFull (Queue Q)
{
	return Q->Size == Q->Capacity;
}

Queue CreateQueue (int MaxElements)
{
	Queue Q;
	if (MaxElements < MinQueueSize)
		writeerr("Queue size is too small.");
	Q = malloc(sizeof(struct QueueRecord));
	if (Q == NULL)
		writeerr("fail to malloc memeroy.");
	Q->Array = malloc(sizeof(ElementType) * MaxElements);
	if (Q->Array == NULL)
		writeerr("fail to malloc memeroy.");
	Q->Capacity = MaxElements;
	MakeEmpty(Q);
	return Q;
}

void DisposeQueue (Queue Q)
{
	if (Q != NULL) {
		free(Q->Array);
		free(Q);
	}
}

void MakeEmpty (Queue Q)
{
	Q->Size = 0;
	Q->Front = 0;
	Q->Rear = 0;
}

static int Succ (Queue Q, int Value)
{
	if (++Value == Q->Capacity)
		Value = 0;
	return Value;
}

void Enqueue (Queue Q, ElementType X)
{
	if (IsFull(Q))
		writeerr("Queue is full.");
	else {
		Q->Size++;
		Q->Rear = Succ(Q, Q->Rear);
		Q->Array[Q->Rear] = X;
	}
}

ElementType Front (Queue Q)
{
	if (!IsEmpty(Q))
		return Q->Array[Q->Front+1];
	writeerr("Queue is empty.");
	return 0;
}

void Dequeue (Queue Q)
{
	if (IsEmpty(Q))
		writeerr("Queue is empty.");
	else {
		Q->Size--;
		Q->Front = Succ(Q, Q->Front);
	}
}

static void dump_queue (Queue Q)
{
	for (int i = Q->Front + 1; i <= Q->Rear; i++) {
		printf("%d\n", Q->Array[i]);
	}
}

int main(int argc, char const *argv[])
{

	Queue Q = CreateQueue(10);
	Enqueue(Q, 1);
	Enqueue(Q, 2);
	Enqueue(Q, 3);
	Enqueue(Q, 4);
	dump_queue(Q);
	printf("\n");
	printf("->%d\n", Front(Q));
	Dequeue(Q);
	printf("->%d\n", Front(Q));
	Dequeue(Q);
	printf("->%d\n", Front(Q));
	printf("\n");
	dump_queue(Q);

	return 0;
}

