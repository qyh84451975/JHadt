#include "HashQuad.h"
#include "../common.h"

#include <stdlib.h>
#define MinTableSize (10)

enum KindOfEntry {Legitimate, Empty, Deleted};

struct HashEntry {
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl {
	int TableSize;
	Cell *TheCells;
};

static int NextPrime (int N)
{
    int i;

    if( N % 2 == 0 )
        N++;
    for( ; ; N += 2 )
    {
        for( i = 3; i * i <= N; i += 2 )
            if( N % i == 0 )
                goto ContOuter;
        return N;
      ContOuter: ;
    }
}

Index Hash (ElementType Key, int TableSize)
{
	return Key % TableSize;
}

HashTable Initialize (int TableSize)
{
	HashTable H;
	int i;
	if (TableSize < MinTableSize)
		return NULL;
	H = malloc(sizeof(struct HashTbl));
	H->TableSize NextPrime(TableSize);
	H->TheCells = malloc(sizeof(Cell) * H->TableSize);
	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;
	return H;
}

void DestroyTable (HashTable H)
{
	free(H->TheCells);
	free(H);
}

Position Find (HashTable H, ElementType Key)
{
	Position CurrPos;
	int CollisionNum;
	CollisionNum = 0;
	CurrPos = Hash(Key, H->TableSize);
	while (H->TheCells[CurrPos].Info != Empty && H->TheCells[CurrPos].Element != Key) {
		CurrPos += 2 * ++CollisionNum - 1;
		if (CurrPos >= H->TableSize)
			CurrPos -= H->TableSize;
	}
	return CurrPos;
}

void Insert (HashTable H, ElementType Key)
{
	Position Pos;
	Pos = Find(H, Key);
	if (H->TheCells[Pos].Info != Legitimate) {
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = Key;
	}
}

HashTable Rehash (HashTable H)
{
	int i, OldSize;
	Cell *OldCells;
	OldCells = H->TheCells;
	OldSize = H->TableSize;
	H = Initialize(2 * OldSize);
	for (i = 0; i < OldSize; i++)
		if (OldCells[i].Info == Legitimate)
			Insert(H, OldCells[i].Element);
	free(OldCells);
	return H;
}

