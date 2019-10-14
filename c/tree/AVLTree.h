#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
typedef int ElementType;

AvlTree MakeEmpty (AvlTree T);
Position Find (AvlTree T, ElementType X);
Position FindMin (AvlTree T);
Position FindMax (AvlTree T);
AvlTree Insert (AvlTree T, ElementType X);
AvlTree Delete (AvlTree T, ElementType X);

#endif /* __AVL_TREE_H__ */