#include "searchTree.h"
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T)
{
    if (T == NULL) {
        return NULL;
    }
    if (T->Element > X) {
        return Find(X, T->Left);
    } else if (T->Element < X) {
        return Find(X, T->Right);
    } else {
        return T;
    }
}

Position FindMin(SearchTree T)
{
    if (T == NULL) {
        return NULL;
    }
    if (T->Left != NULL) {
        return FindMin(T->Left);
    } else {
        return T;
    }
}

Position FindMax(SearchTree T)
{
    if (T == NULL) {
        return NULL;
    }
    while (T->Right) {
        T = T->Right;
    }
    return T;
}

SearchTree Insert(ElementType X, SearchTree T)
{
    if (T == NULL) {
        T = (SearchTree)malloc(sizeof(struct TreeNode));
        if (T == NULL) {
            printf("Out of space!\n");
            return T;
        }
        T->Element = X;
        T->Left = NULL;
        T->Right = NULL;
    } else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
    } else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
    }
    return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;
    if (T == NULL) {
        printf("Element Not Found!\n");
        return T;
    } else if (X < T->Element) {
        T->Left = Delete(X, T->Left);
    } else if (X > T->Element) {
        T->Right = Delete(X, T->Right);
    } else if (T->Left && T->Right) {
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    } else {
        TmpCell = T;
        if (T->Left == NULL) {
            T = T->Right;
        } else if (T->Right == NULL) {
            T = T->Left;
        }
        free(TmpCell);
    }

    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}