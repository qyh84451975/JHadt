#ifndef hahs_sep_h
#define hahs_sep_h

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef int ElementType;

HashTable Initialize (int TableSize);
void DestroyTable (HashTable H);
Position Find (HashTable H, ElementType Key);
void Insert (HashTable H, ElementType Key);

#endif /* hahs_sep_h */