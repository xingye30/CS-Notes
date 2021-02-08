#include "stack(list).h"
#include <stdio.h>
#include <stdlib.h>

struct Node {
    ElementType element;
    PtrToNode Next;
};

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack(void)
{
    Stack stack = (Stack)malloc(sizeof(struct Node));
    stack->Next = NULL;
    return stack;
}

void DisposeStack(Stack S)
{
    while (S->Next != NULL) {
        Pop(S);
    }
}

void MakeEmpty(Stack S)
{
    DisposeStack(S);
    S->Next = NULL;
}

void Push(ElementType X, Stack S)
{
    PtrToNode node = (PtrToNode)malloc(sizeof(struct Node));
    node->element = X;
    node->Next = S->Next;
    S->Next = node;
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Next->element;
    return 0;
}

void Pop(Stack S)
{
    PtrToNode tmp = S->Next;
    S->Next = tmp->Next;
    free(tmp);
}