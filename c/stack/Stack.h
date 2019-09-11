#ifndef __STACK__
#define __STACK__

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node *next;
} Node;

typedef struct Stack
{
	Node *top;
	int count;
} Stack;

Status Init(Stack *S);
Status Push(Stack *S, ElemType e);
Status Pop(Stack *S, ElemType *e);
int Count(Stack *S);


#endif /* __STACK__ */