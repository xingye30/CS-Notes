#include "binHeap.h"
#include <stdio.h>
#include <stdlib.h>

struct HeapStruct {
    int Capacity;
    int Size;
    ElementType *Elements;
};
#define MinData -1

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if (H == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    H->Elements = (ElementType*)malloc(sizeof(ElementType) * (MaxElements + 1));
    if (H->Elements == NULL) {
        printf("Out of space!\n");
        free(H);
        return NULL;
    }
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;
    return H;
}

void Destroy(PriorityQueue H)
{
    free(H->Elements);
    free(H);
}

void MakeEmpty(PriorityQueue H)
{
    H->Capacity = 0;
    H->Size = 0;
    free(H->Elements);
    H->Elements = NULL;
}

void Insert(ElementType X, PriorityQueue H)
{
    if (IsFull(H)) {
        ElementType *tmp = H->Elements;
        H->Elements = (ElementType*)malloc(sizeof(ElementType) * (H->Capacity*2 + 1));
        if (H->Elements == NULL) {
            printf("Out of space\n");
            H->Elements = tmp;
            return;
        }
        for (int i = 0; i < H->Capacity; i++) {
            H->Elements[i+1] = tmp[i+1];
        }
        free(tmp);
        H->Capacity = H->Capacity * 2 + 1;
    }
    int i;
    for (i = ++H->Size; H->Elements[i/2] > X; i = i / 2) {
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{   
    int i, child;
    ElementType MinElement, LastElement;

    if (IsEmpty(H)) {
        printf("Priority queue is empty!\n");
        return H->Elements[0];
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for (i = 1; i * 2 <= H->Size; i = child) {
        child = i * 2;
        if (child != H->Size && H->Elements[Child + 1] < H->Elements[child]) {
            child++;
        }
        if (LastElement > H->Elements[child]) {
            H->Elements[i] = H->Elements[child];
        } else {
            break;
        }
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

ElementType FindMin(PriorityQueue H)
{
    return H->Elements[1];
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
    return H->Capacity == H->Size;
}
