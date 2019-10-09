#ifndef __ARRAY_QUEUE_H__
#define __ARRAY_QUEUE_H__

struct QueueRecord;
typedef struct QueueRecord *Queue;

typedef int ElementType;

int IsEmpty (Queue Q);
int IsFull (Queue Q);
Queue CreateQueue (int MaxElements);
void DisposeQueue (Queue Q);
void MakeEmpty (Queue Q);
void Enqueue (Queue Q, ElementType X);
ElementType Front (Queue Q);
void Dequeue (Queue Q);

#endif /* __ARRAY_QUEUE_H__ */