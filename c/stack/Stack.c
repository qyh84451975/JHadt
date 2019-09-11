#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

Status Init(Stack *S)
{
	S->count = 0;
	return OK;
}

int Count(Stack *S)
{
	return S->count;
}

Status Push(Stack *S, ElemType e)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = e;
	node->next = S->top;
	S->top = node;
	S->count++;
	return OK;
}

Status Pop(Stack *S, ElemType *e)
{
	if (S->count == 0) return ERROR;
	*e = S->top->data;
	Node *node;
	node = S->top;
	S->top = S->top->next;
	free(node);
	S->count--;
	return ERROR;
}

void _dump_stack(Stack *S)
{
	Node *node;
	node = S->top;
	while(node) {
		printf("stack data: %d\n", node->data);
		node = node->next;
	}
}