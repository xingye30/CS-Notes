#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node {
    ElementType Element;
    Position Next;
};

List MakeEmpty(List L)
{
    DeleteList(L);
    L->Next = NULL;
    return L;
}

/* Return true if L is empty */
int IsEmpty(List L)
{
    return L->Next == NULL;
}

/* Return true if P is the last position in list L */
int IsLast(Position P, List L)
{
    while (L->Next != NULL) {
        L = L->Next;
    }
    return P == L;
}

/* Return Position of X in L; NULL if not found */
Position Find(ElementType X, List L)
{
    Position P = L->Next;
    while (P != NULL && P->Element != X) {
        L = L->Next;
    }
    return L;
}

/* Delete first occurrence of X from a list */
void Delete(ElementType X, List L)
{
    Position P = L->Next;
    while(P != NULL && P->Next != NULL && P->Next->Element != X) {
        P = P->Next;
    }
    Position tmp = P->Next;
    P->Next = P->Next->Next;
    free(tmp);
}

/* If X is not found, then Next field of returned Position is NULL */
Position FindPrevious(ElementType X, List L)
{
    while (L->Next != NULL && L->Next->Element != X) {
        L = L->Next;
    }
    return L;
}

/* Insert after position P */
void Insert(ElementType X, List L, Position P)
{
    Position tmp = (Position)malloc(sizeof(struct Node));
    tmp->Element = X;
    tmp->Next = P->Next;
    P->Next = tmp;
}

void DeleteList(List L)
{
    Position tmp, P;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL) {
        tmp = P;
        P = P->Next;
        free(tmp);
    }
}

Position Header(List L)
{
    return L;
}

Position First(List L)
{
    return L->Next;
}

Position Advance(Position P)
{
    return P->Next;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}