#include "hashSep.h"
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    ElementType Element;
    Position Next;
};

typedef Position List;
struct HashTbl {
    List* TheLists;
    int TableSize;
};

HashTable InitializeTable(int TableSize)
{
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
    if (H == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    H->TheLists = (List*)malloc(sizeof(List) * TableSize);
    if (H->TheLists == NULL) {
        printf("Out of space!\n");
        return NULL;
    }
    H->TableSize = TableSize;
    for (int i = 0; i < H->TableSize; i++) {
        H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
        if (H->TheLists[i] == NULL) {
            printf("Out of space!\n");
            return NULL;
        } else {
            H->TheLists[i]->Next = NULL;
        }
    }
    
    return H;
}

void DestroyTable(HashTable H)
{
    if (H == NULL) {
        return;
    }
    for (int i = 0; i < H->TableSize; i++) {
        if (H->TheLists[i] != NULL) {
            while (H->TheLists[i]->Next != NULL) {
                Position tmp = H->TheLists[i]->Next;
                H->TheLists[i]->Next = tmp->Next;
                free(tmp);
            }
            free(H->TheLists[i]);
        }
    }
    free(H);
}

Position Find(ElementType Key, HashTable H)
{
    Position P;
    List L;
    L = H->TheLists[Hash(Key, H->TableSize)];
    P = L->Next;
    while (P != NULL && P->Element != Key) {
        P = P->Next;
    }
    return P;
}

void Insert(ElementType Key, HashTable H)
{
    Position Pos;
    List L;
    Pos = Find(Key, H);
    if (Pos == NULL) {
        Position tmp = (Position)malloc(sizeof(struct ListNode));
        if (tmp == NULL) {
            printf("Out of space!\n");
            return NULL;
        }
        L = H->TheLists[Hash(Key, H->TableSize)];
        tmp->Element = Key;
        tmp->Next = L->Next;
        L->Next = tmp;
    }
}

ElementType Retrieve(Position P)
{
    return P->Element;
}