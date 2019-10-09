#ifndef __STACK_H__
#define __STACK_H__

struct Node;

typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
// 假设存储数据为整型
typedef int ElementType;

int IsEmpty (Stack S);
Stack CreateStack (void);
void MakeEmpty (Stack S);
void DisposeStack (Stack S);
void Push (Stack S, ElementType X);
ElementType Top (Stack S);
ElementType Pop (Stack S);

#endif /* __STACK_H__ */