#include "ArrayStack.h"
#include "../common.h"
#include <stdlib.h>

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord {
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};

int IsEmpty (Stack S)
{
	return S->TopOfStack == EmptyTOS;
}

int IsFull (Stack S)
{
	return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack (int MaxElements)
{
	Stack S;
	if (MaxElements < MinStackSize)
		writeerr("Stack size is too small.");
	S = malloc(sizeof(struct StackRecord));
	if (S == NULL)
		writeerr("fail to malloc memeroy.");
	S->Array = malloc(sizeof(ElementType) * MaxElements);
	if (S->Array == NULL)
		writeerr("fail to malloc memeroy.");
	S->Capacity = MaxElements;
	MakeEmpty(S);
	return S;
}

void DisposeStack (Stack S)
{
	if (S != NULL) {
		free(S->Array);
		free(S);
	}
}

void MakeEmpty (Stack S)
{
	S->TopOfStack = EmptyTOS;
}

void Push (Stack S, ElementType X)
{
	if (IsFull(S))
		writeerr("Stack is full.");
	else
		S->Array[++S->TopOfStack] = X;
}

ElementType Top (Stack S)
{
	if (!IsEmpty(S))
		return S->Array[S->TopOfStack];
	writeerr("Top empty Stack.");
	return 0;
}

ElementType Pop (Stack S, int status)
{
	if (IsEmpty(S)) {
		printf("pop empty stack status: %d\n", status);
		writeerr("Pop empty Stack.");
	}
	else
		return S->Array[S->TopOfStack--];
}

static void dump_stack (Stack S)
{
	int top = S->TopOfStack;
	while (top != EmptyTOS) {
		printf("%c\n", S->Array[top--]);
	}
}

#include <string.h>
static char priority[6][2] = {{'+', 'a'}, {'-', 'a'}, {'*', 'b'}, {'/', 'b'}, {'(', 'c'}, {')', 'c'}};
static int cmp (char a, char b)
{
	char apri = 'a';
	char bpri = 'a';
	for (int i = 0; i < 6; i++) {
		if (priority[i][0] == a) {
			apri = priority[i][1];
		}
		if (priority[i][0] == b) {
			bpri = priority[i][1];
		}
	}

	return apri >= bpri;
}

static int isOperator (char a)
{
	for (int i = 0; i < 6; i++) {
		if (a == priority[i][0])
			return 1;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
/*
	Stack S = CreateStack(20);
	Push(S, 1);
	Push(S, 2);
	Push(S, 3);
	Push(S, 4);
	Push(S, 5);
	dump_stack(S);
	printf("\n");
	Pop(S);
	dump_stack(S);
*/

// 中缀表达式转后缀表达式

	Stack S1 = CreateStack(20);
	Stack S2 = CreateStack(20);

	const char *exp = "a+b*c+(d*e+f)*g";
	unsigned int len = strlen(exp);
	unsigned int max = len;
	int i = 0;
	while (len--) {
		char c = exp[i];

		if (i == max - 1) {
			Push(S1, c);
			while (!IsEmpty(S2)) {
				Push(S1, Pop(S2, 1));
			}
		}
		else {
			if (isOperator(c)) {
				if (c == ')') {
					while (!IsEmpty(S2) && Top(S2) != '(') {
						Push(S1, Pop(S2, 2));
					}
					Pop(S2, 3);
				}
				else {
					while (!IsEmpty(S2) && Top(S2) != '(' && cmp(Top(S2), c)) {
						Push(S1, Pop(S2, 4));
					}
					Push(S2, c);
				}
			}
			else {
				Push(S1, c);
			}
		}

		i++;
	}

	dump_stack(S1);
// 后缀表达式转表达式树
// 1.将后缀表达式，依次从栈S3读出。
// 2.遇到操作数就创建一个叶子节点，节点指针入栈S4。
// 3.遇到操作符就创建一个父节点，左右子节点依次为S4中的栈顶弹出的两个节点指针。然后将父节点入栈S4。
// 4.直到读完S3元素，表达式树构造完成。
// 伪代码
/*
	while (!IsEmpty(S3)) {
		char ele = Pop(S3);
		if (isOperator(ele)) {
			TreeNode T = malloc(sizeof(struct TreeNode));
			T->Element = ele;
			T->Left = Pop(S4);
			T->Right = Pop(S4);
			Push(S4, T);
		}
		else {
			TreeNode T = malloc(sizeof(struct TreeNode));
			T->Element = ele;
			T->Left = NULL;
			T->Right = NULL;
			Push(S4, T);
		}
	}
*/
	return 0;
}

