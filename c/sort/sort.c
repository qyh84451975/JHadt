#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

// 插入排序
void InsertionSort(ElementType A[], int N)
{
	int j, P;
	ElementType Tmp;
	// 1 ~ N-1
	for (P = 1; P < N; P++) {
		// 准备移动第P个元素
		Tmp = A[P];
		// 开始比较P位置上的元素，依次右移各个不满足条件的元素
		for (j = P; j > 0 && A[j-1] > Tmp; j--) {
			A[j] = A[j-1];
		}
		// 此时j的位置为可插入位置
		A[j] = Tmp;
	}
}

// 希尔排序
void ShellSort(ElementType A[], int N)
{
	int i, j, Increment;
	ElementType Tmp;
	for (Increment = N/2; Increment > 0; Increment /= 2) {
		for (i = Increment; i < N; i++) {
			Tmp = A[i];
			for (j = i; j >= Increment; j -= Increment) {
				if (Tmp < A[j-Increment]) {
					A[j] = A[j-Increment];
				}
				else {
					break;
				}
			}
			A[j] = Tmp;
		}
	}
}

// 堆排序
#define LeftChild(i) (2*(i)+1)

void Swap(ElementType *Lhs, ElementType *Rhs)
{
	ElementType Tmp = *Lhs;
	*Lhs = *Rhs;
	*Rhs = Tmp;
}

void PercDown(ElementType A[], int i, int N)
{
	int Child;
	ElementType Tmp;
	for (Tmp = A[i]; LeftChild(i) < N; i = Child) {
		Child = LeftChild(i);
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child ++;
		if (Tmp < A[Child])
			A[i] = A[Child];
		else break;
	}
	A[i] = Tmp;
}

void HeapSort(ElementType A[], int N)
{
	int i;
	for (i = N/2; i >= 0; i--)
		PercDown(A, i, N);
	for (i = N-1; i > 0; i--) {
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
	}
}

// 归并排序
void Merge( ElementType A[ ], ElementType TmpArray[ ],
                        int Lpos, int Rpos, int RightEnd )
{
    int i, LeftEnd, NumElements, TmpPos;

    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    while( Lpos <= LeftEnd && Rpos <= RightEnd )
        if( A[ Lpos ] <= A[ Rpos ] )
            TmpArray[ TmpPos++ ] = A[ Lpos++ ];
        else
            TmpArray[ TmpPos++ ] = A[ Rpos++ ];

    while( Lpos <= LeftEnd )  /* Copy rest of first half */
        TmpArray[ TmpPos++ ] = A[ Lpos++ ];
    while( Rpos <= RightEnd ) /* Copy rest of second half */
        TmpArray[ TmpPos++ ] = A[ Rpos++ ];

    /* Copy TmpArray back */
    for( i = 0; i < NumElements; i++, RightEnd-- )
        A[ RightEnd ] = TmpArray[ RightEnd ];
}

void MSort( ElementType A[ ], ElementType TmpArray[ ],
                        int Left, int Right )
{
    int Center;

    if( Left < Right )
    {
        Center = ( Left + Right ) / 2;
        MSort( A, TmpArray, Left, Center );
        MSort( A, TmpArray, Center + 1, Right );
        Merge( A, TmpArray, Left, Center + 1, Right );
    }
}

void Mergesort( ElementType A[ ], int N )
{
    ElementType *TmpArray;

    TmpArray = malloc( N * sizeof( ElementType ) );
    if( TmpArray != NULL )
    {
        MSort( A, TmpArray, 0, N - 1 );
        free( TmpArray );
    }
}

// 快速排序
ElementType Median3( ElementType A[ ], int Left, int Right )
{
    int Center = ( Left + Right ) / 2;

    if( A[ Left ] > A[ Center ] )
        Swap( &A[ Left ], &A[ Center ] );
    if( A[ Left ] > A[ Right ] )
        Swap( &A[ Left ], &A[ Right ] );
    if( A[ Center ] > A[ Right ] )
        Swap( &A[ Center ], &A[ Right ] );

    /* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */

    Swap( &A[ Center ], &A[ Right - 1 ] );  /* Hide pivot */
    return A[ Right - 1 ];                /* Return pivot */
}

#define Cutoff ( 3 )

void Qsort( ElementType A[ ], int Left, int Right )
{
    int i, j;
    ElementType Pivot;

	if( Left + Cutoff <= Right )
    {
  		Pivot = Median3( A, Left, Right );
  		i = Left; j = Right - 1;
  		for( ; ; )
        {
      		while( A[ ++i ] < Pivot ){ }
      		while( A[ --j ] > Pivot ){ }
      		if( i < j )
          		Swap( &A[ i ], &A[ j ] );
            else
          		break;
        }
  		Swap( &A[ i ], &A[ Right - 1 ] );

  		Qsort( A, Left, i - 1 );
  		Qsort( A, i + 1, Right );
    }
    else
        InsertionSort( A + Left, Right - Left + 1 );
}
void Quicksort( ElementType A[ ], int N )
{
    Qsort( A, 0, N - 1 );
}

void dump_arr(ElementType A[], int N)
{
	int i;
	for (i = 0; i < N; i++) {
		printf("%d\n", A[i]);
	}
}

int main(int argc, char const *argv[])
{

	ElementType a[] = {38, 8, 64, 51, 32, 21};
	// InsertionSort(a, 6);
	// ShellSort(a, 6);
	// HeapSort(a, 6);
	// Mergesort(a, 6);
	Quicksort(a, 6);
	dump_arr(a, 6);

	return 0;
}