#ifndef __LINEAR_LIST__
#define __LINEAR_LIST__

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;


// 线性顺序存储，用数组实现
#define MAX_SIZE 20

typedef struct
{
	ElemType data[MAX_SIZE];
	int length; // 线性表当前长度
} SqList;

Status Init_seq(SqList *L);
// 获取元素
Status GetElem_seq(SqList L, int i, ElemType *e);
// 插入
// 如果在中间插入，需要大量移动之后的元素
Status Insert_seq(SqList *L, int i, ElemType e);
// 删除
Status Delete_seq(SqList *L, int i, ElemType *e);

// 链式存储
// 单向链表
typedef struct Node
{
	ElemType data;
	struct Node *next;
} Node;
typedef struct Node *LinkList;
Status Init_1(LinkList *L);
Status GetElem_1(LinkList L, int i, ElemType *e);
Status Insert_1(LinkList *L, int i, ElemType e);
Status Delete_1(LinkList *L, int i, ElemType *e);

#endif /* __LINEAR_LIST__ */