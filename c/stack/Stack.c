#include "Stack.h"
#include "../common.h"
#include <stdlib.h>

struct Node {
	ElementType Element;
	PtrToNode Next;
};

int IsEmpty (Stack S)
{
	return S->Next == NULL;
}

Stack CreateStack (void)
{
	Stack S;
	S = malloc(sizeof(struct Node));
	if (S == NULL)
		writeerr("fail to malloc memeroy.");
	S->Next = NULL;
	MakeEmpty(S);
	return S;
}

void MakeEmpty (Stack S)
{
	if (S == NULL) {
		writeerr("pls CreateStack first.");
	}
	else {
		while (!IsEmpty(S)) {
			Pop(S);
		}
	}
}

void DisposeStack (Stack S)
{
	MakeEmpty(S);
	free(S);
}

void Push (Stack S, ElementType X)
{
	PtrToNode newNode = malloc(sizeof(struct Node));
	if (newNode == NULL)
		writeerr("fail to malloc memeroy.");
	newNode->Element = X;
	newNode->Next = S->Next;
	S->Next = newNode;
}

ElementType Top (Stack S)
{
	if (!IsEmpty(S))
		return S->Next->Element;
	writeerr("cannot top empty stack.");
	return 0;
}

ElementType Pop (Stack S)
{
	if (!IsEmpty(S)) {
		PtrToNode temp = S->Next;
		S->Next = temp->Next;
		ElementType elem = temp->Element;
		free(temp);
		return elem;
	}
	writeerr("cannot pop empty stack.");
	return 0;
}

static void dump_stack (Stack S)
{
	PtrToNode temp = S->Next;
	while (temp) {
		printf("%d\n", temp->Element);
		temp = temp->Next;
	}
}

int main(int argc, char const *argv[])
{
	Stack s = CreateStack();
	Push(s, 1);
	Push(s, 2);
	Push(s, 3);
	Push(s, 4);
	dump_stack(s);
	printf("pop = %d\n", Pop(s));
	printf("top = %d\n", Top(s));
	printf("pop = %d\n", Pop(s));
	printf("top = %d\n", Top(s));
	dump_stack(s);




	return 0;
}