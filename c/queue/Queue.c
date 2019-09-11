#include <stdlib.h>
#include "Queue.h"

Status InitQueue(Queue *Q)
{
	Q->front = Q->rear = NULL;
}

Status EnQueue(Queue *Q, ElemType e)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = e;
	node->next = NULL;
	Q->rear->next = node;
	Q->rear = node;
	return OK;
}

Status DeQueue(Queue *Q, ElemType *e)
{
	Node *node;
	if (Q->front == Q->rear) return ERROR;
	node = Q->front->next;
	*e = node->data;
	Q->front->next = node->next;
	if (Q->rear == node)
		Q->rear = Q->front;
	free(node);
	return OK;
}