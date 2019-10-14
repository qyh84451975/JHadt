#ifndef hash_quad_h
#define hash_quad_h

// 开放定址
typedef unsigned int Index;
typedef Index Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef int ElementType;

HashTable Initialize (int TableSize);
void DestroyTable (HashTable H);
Position Find (HashTable H, ElementType Key);
void Insert (HashTable H, ElementType Key);
HashTable Rehash (HashTable H);


#endif /* hash_quad_h */