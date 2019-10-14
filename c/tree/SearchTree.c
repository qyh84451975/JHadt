#include "SearchTree.h"
#include "../common.h"
#include <stdlib.h>

struct TreeNode {
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};

SearchTree MakeEmpty (SearchTree T)
{
	if (T != NULL) {
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find (SearchTree T, ElementType X)
{
	if (T == NULL)
		return NULL;
	if (X < T->Element) {
		return Find(T->Left, X);
	}
	else {
		if (X > T->Element)
			return Find(T->Right, X);
		else
			return T;
	}
}

Position FindMin (SearchTree T)
{
	if (T == NULL) {
		return NULL;
	}
	else {
		if (T->Left == NULL)
			return T;
		else
			return FindMin(T->Left);
	}

}

Position FindMax (SearchTree T)
{
	if (T != NULL) {
		while(T->Right != NULL)
			T = T->Right;
	}
	return T;
}

SearchTree Insert (SearchTree T, ElementType X)
{
	if (T == NULL) {
		T = malloc(sizeof(struct TreeNode));
		if (T == NULL) {
			writeerr("fail to malloc.");
		}
		else {
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else {
		if (X < T->Element) {
			T->Left = Insert(T->Left, X);
		}
		else {
			if (X > T->Element)
				T->Right = Insert(T->Right, X);
		}
	}
	return T;
}

SearchTree Delete (SearchTree T, ElementType X)
{
	Position temp;
	if (T == NULL) {
		writeerr("not found.");
	}
	else {
		if (X < T->Element) {
			T->Left = Delete(T->Left, X);
		}
		else {
			if (X > T->Element) {
				T->Right = Delete(T->Right, X);
			}
			else {
				if (T->Left && T->Right) {
					temp = FindMin(T->Right);
					T->Element = temp->Element;
					T->Right = Delete(T->Right, T->Element);
				}
				else {
					temp = T;
					if (T->Left == NULL) {
						T = T->Right;
					}
					else if (T->Right == NULL) {
						T = T->Left;
					}
					free(temp);
				}
			}
		}
	}
	return T;
}

ElementType Retrieve (Position P)
{
	return P->Element;
}
