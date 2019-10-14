#ifndef __SEARCH_TREE_H__
#define __SEARCH_TREE_H__

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElementType;

SearchTree MakeEmpty (SearchTree T);
Position Find (SearchTree T, ElementType X);
Position FindMin (SearchTree T);
Position FindMax (SearchTree T);
SearchTree Insert (SearchTree T, ElementType X);
SearchTree Delete (SearchTree T, ElementType X);
ElementType Retrieve (Position P);

#endif /* __SEARCH_TREE_H__ */