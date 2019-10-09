#include "ArrayStack.h"
#include "../common.h"
#include <stdlib.h>

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord {
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};

int IsEmpty (Stack S)
{
	return S->TopOfStack == EmptyTOS;
}

int IsFull (Stack S)
{
	return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack (int MaxElements)
{
	Stack S;
	if (MaxElements < MinStackSize)
		writeerr("Stack size is too small.");
	S = malloc(sizeof(struct StackRecord));
	if (S == NULL)
		writeerr("fail to malloc memeroy.");
	S->Array = malloc(sizeof(ElementType) * MaxElements);
	if (S->Array == NULL)
		writeerr("fail to malloc memeroy.");
	S->Capacity = MaxElements;
	MakeEmpty(S);
	return S;
}

void DisposeStack (Stack S)
{
	if (S != NULL) {
		free(S->Array);
		free(S);
	}
}

void MakeEmpty (Stack S)
{
	S->TopOfStack = EmptyTOS;
}

void Push (Stack S, ElementType X)
{
	if (IsFull(S))
		writeerr("Stack is full.");
	else
		S->Array[++S->TopOfStack] = X;
}

ElementType Top (Stack S)
{
	if (!IsEmpty(S))
		return S->Array[S->TopOfStack];
	writeerr("empty Stack.");
	return 0;
}

void Pop (Stack S)
{
	if (IsEmpty(S))
		writeerr("empty Stack.");
	else
		S->TopOfStack--;
}

static void dump_stack (Stack S)
{
	int top = S->TopOfStack;
	while (top != EmptyTOS) {
		printf("%d\n", S->Array[top--]);
	}
}


int main(int argc, char const *argv[])
{

	Stack S = CreateStack(20);
	Push(S, 1);
	Push(S, 2);
	Push(S, 3);
	Push(S, 4);
	Push(S, 5);
	dump_stack(S);
	printf("\n");
	Pop(S);
	dump_stack(S);


	return 0;
}

