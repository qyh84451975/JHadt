#ifndef __ARRAY_STACK_H__
#define __ARRAY_STACK_H__

// 栈的数组实现
// 创建栈的时候，提前申请固定大小容量数组
// 每次存储数据只是移动游标的位置(栈顶游标)
struct StackRecord;
typedef struct StackRecord *Stack;

typedef int ElementType;

int IsEmpty (Stack S);
int IsFull (Stack S);
Stack CreateStack (int MaxElements);
void DisposeStack (Stack S);
void MakeEmpty (Stack S);
void Push (Stack S, ElementType X);
ElementType Top (Stack S);
void Pop (Stack S);

#endif /* __ARRAY_STACK_H__ */