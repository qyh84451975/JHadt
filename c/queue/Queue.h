#ifndef __QUEUE__
#define __QUEUE__

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

typedef struct
{
	Node *front, *rear;
} Queue;

Status InitQueue(Queue *Q);

Status EnQueue(Queue *Q, ElemType e);

Status DeQueue(Queue *Q, ElemType *e);

#endif /* __QUEUE__ */