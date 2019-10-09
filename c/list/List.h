/*************
 *   单链表   *
 *************/

#ifndef __LIST_H__
#define __LIST_H__

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

// 假设存储数据为整型
typedef int ElementType;

List MakeEmpty (List L);
int IsEmpty (List L);
int IsLast (List L, Position P);
Position Find (List L, ElementType X);
void Delete (List L, ElementType X);
Position FindPrevious (List L, ElementType X);
void Insert (List L, Position P, ElementType X);
void DeleteList (List L);
Position Header (List L);
Position First (List L);
Position Advance (Position P);
ElementType Retrieve (Position P);
Position Next (Position P, List L);


#endif /* __LIST_H__ */