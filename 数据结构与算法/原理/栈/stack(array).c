#include "stack(array).h"
#include <stdio.h>
#include <stdlib.h>

#define EmptyTOS  (-1)
#define MinStackSize (5)
struct StackRecord {
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
    return S->TopOfStack + 1 == S->Capacity;
}

Stack CreateStack(int MaxElements)
{
    if (MaxElements < MinStackSize) {
        printf("Stack size is too small!\n");
        return NULL;
    }
    Stack S = (Stack)malloc(sizeof(struct StackRecord));
    if (S == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    S->Array = (ElementType*)malloc(sizeof(ElementType) * MaxElements);
    if (S->Array == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    S->Capacity = MaxElements;
    MakeEmpty(S);
    return S;
}

void DisposeStack(Stack S)
{
    if (S != NULL) {
        free(S->Array);
        free(S);
    }
}

void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}

void Push(ElementType X, Stack S)
{
    if (IsFull(S)) {
        ElementType *tmp = S->Array;
        int tmpSize = S->Capacity;
        S->Array = (ElementType*)malloc(sizeof(ElementType) * S->Capacity * 2);
        if (S->Array == NULL) {
            printf("malloc error!\n");
            S->Array = tmp;
            return;
        }
        S->Capacity = S->Capacity * 2;
        for (int i = 0; i < tmpSize; i++) {
            S->Array[i] = tmp[i];
        }
    }
    S->TopOfStack + 1;
    S->Array[S->TopOfStack] = X;
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S)) {
        return S->Array[S->TopOfStack];
    }
    printf("Empty Stack!\n");
    return 0;
}

void Pop(Stack S)
{
    if (!IsEmpty(S)) {
        S->TopOfStack = S->TopOfStack - 1;
    }
    printf("Empty Stack!\n");
}

ElementType TopAndPop(Stack S)
{
    if (!IsEmpty(S)) {
        ElementType top = S->Array[S->TopOfStack];
        S->TopOfStack = S->TopOfStack - 1;
        return top;
    }
    printf("Empty Stack!\n");
    return 0;
}

