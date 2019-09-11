#include <stdlib.h>
#include "LinearList.h"

Status Init_seq(SqList *L)
{
	L->length = 0;
	return OK;
}

Status GetElem_seq(SqList L, int i, ElemType *e)
{
	if (L.length == 0 || i < 1 || i > L.length) {
		return ERROR;
	}
	*e = L.data[i-1];
	return OK;
}

Status Insert_seq(SqList *L, int i, ElemType e)
{
	int k;
	if (L->length == MAX_SIZE) {
		return ERROR;
	}
	if (i < 1 || i > L->length+1) {
		return ERROR;
	}
	if (i <= L->length) {
		for (k = L->length-1; k >= i - 1; k--) {
			L->data[k+1] = L->data[k];
		}
	}
	L->data[i-1] = e;
	L->length++;
	return OK;
}

Status Delete_seq(SqList *L, int i, ElemType *e)
{
	int k;
	if (L->length == 0) {
		return ERROR;
	}
	if (i < 1 || i > L->length) {
		return ERROR;
	}
	*e = L->data[i-1];
	if (i < L->length) {
		for (k = i; k < L->length; k++) {
			L->data[k-1] = L->data[k];
		}
	}
	L->length--;
	return OK;
}

Status Init_1(LinkList *L)
{
	(*L)->next = NULL;
	return OK;
}

Status GetElem_1(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;
	p = L->next;
	j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) {
		return ERROR;
	}
	*e = p->data;
	return OK;
}

Status Insert_1(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p;
	Node *node;
	p = *L;
	j = 1;
	while(p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) {
		return ERROR;
	}

	// void* malloc(int byte_num);
	node = (Node*)malloc(sizeof(Node));
	node->data = e;
	node->next = p->next;
	p->next = node;
	return OK;
}

Status Delete_1(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p;
	Node *node;
	p = *L;
	j = 1;
	while(p->next && j < i) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i) {
		return ERROR;
	}
	node = p->next;
	p->next = node->next;
	*e = node->data;
	free(node);
	return OK;
}
















