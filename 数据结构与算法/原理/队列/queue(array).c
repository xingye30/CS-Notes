#include "queue(array).h"
#include <stdio.h>
#include <stdlib.h>

#define MinQueueSize (5)
struct QueueRecord {
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

int IsFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

Queue CreateQueue(int MaxElements)
{
    if (MaxElements < MinQueueSize) {
        printf("Queue size too small!\n");
        reuturn NULL;
    }
    Queue Q = (Queue)malloc(sizeof(struct QueueRecord));
    if (Q == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    Q->Array = (ElementType*)malloc(sizeof(ElementType) * MaxElements);
    if (Q->Array == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    Q->Capacity = MaxElements;
    MakeEmpty(Q);
    return Q;
}

void DisposeQueue(Queue Q)
{
    if (Q != NULL) {
        free(Q->Array);
        free(Q);
    }
}

void MakeEmpty(Queue Q)
{
    if (Q != NULL) {
        Q->Size = 0;
        Q->Front = 1;
        Q->Rear = 0;
    }
}

static int Succ(int Value, Queue Q)
{
    if (++Value == Q->Capacity) {
        Value = 0;
    }
    return Value;
}

void Enqueue(ElementType X, Queue Q)
{
    if (IsFull(Q)) {
        ElementType *tmpArray = Q->Array;
        Q->Array = (ElementType*)malloc(sizeof(ElementType) * Q->Capacity * 2);
        if (Q->Array == NULL) {
            printf("Out of space!\n");
            Q->Array = tmpArray;
            return;
        }
        Q->Capacity *= 2;
    }
    Q->Size++;
    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
}

ElementType Front(Queue Q)
{
    if (!IsEmpty(Q)) {
        return Q->Array[Q->Front];
    } 
    return 0;
}

void Dequeue(Queue Q)
{
    if (!IsEmpty(Q)) {
        Q->Size--;
        Q->Front = Succ(Q->Front, Q);
    }
}

ElementType FrontAndDequeue(Queue Q)
{
    if (!IsEmpty(Q)) {
        Q->Size--;
        ElementType front = Q->Array[Q->Front];
        Q->Front = Succ(Q->Front, Q);
        return front;
    }
    return 0;
}