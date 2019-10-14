#include "AVLTree.h"
#include "../common.h"

#include <stdlib.h>

// avltree 首先是个查找二叉树
// 注意：定义空子树（树叶）高度为-1
// 任何一个节点的左右子树高度相差不超过1

struct AvlNode {
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
}

AvlTree MakeEmpty (AvlTree T)
{
	if( T != NULL ) {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

Position Find (AvlTree T, ElementType X)
{
	if( T == NULL )
        return NULL;
    if( X < T->Element )
        return Find( X, T->Left );
    else
    if( X > T->Element )
        return Find( X, T->Right );
    else
        return T;
}

Position FindMin (AvlTree T)
{
	if( T == NULL )
        return NULL;
    else
    if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

Position FindMax (AvlTree T)
{
	if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

static int Height (Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

static int Max (int Lhs, int Rhs)
{
	return Lhs > Rhs ? Lhs : Rhs;
}

static Position SingleRotateWithLeft (Position K2)
{
	Position K1;
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), K2->Height) + 1;
	return K1;
}

static Position SingleRotateWithRight (Position K1)
{
	Position K2;
	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;
	K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = Max(Height(K2->Right), K1->Height) + 1;
	return K2;
}

static Position DoubleRotateWithLeft (Position K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

static Position DoubleRotateWithRight (Position K1)
{
	K1->Right = SingleRotateWithLeft(K1->Right);
	return SingleRotateWithRight(K1);
}

AvlTree Insert (AvlTree T, ElementType X)
{

}

AvlTree Delete (AvlTree T, ElementType X)
{

}
