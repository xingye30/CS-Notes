#include "AVLTree.h"

struct AvlNode {
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};

AvlTree MakeEmpty(AvlTree T)
{
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return T;
}

Position Find(ElementType X, AvlTree T)
{
    if (T == NULL) {
        return NULL;
    } else if (T->Element > X) {
        return Find(X, T->Left);
    } else if (T->Element < X) {
        return Find(X, T->Right);
    } else {
        return T;
    }
}

Position FindMin(AvlTree T)
{
    if (T == NULL) {
        return NULL;
    } else if (T->Left == NULL) {
        return T;
    } else {
        return FindMin(T->Left);
    }
}

Position FindMax(AvlTree T)
{
    if (T == NULL) {
        return NULL;
    } else if (T->Right == NULL) {
        return T;
    } else {
        return FindMin(T->Right);
    }
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

AvlTree SingleRotateWithLeft(Position k2) //左-左
{
    Position k1;
    k1 = k2->Left;
    k1->Right = k2;
    k2->Left = k1->Right;
    k2->Height = Max(Height(k2->Left), Height(k2->Right)) + 1;
    k1->Height = Max(Height(k1->Left), Height(k1->Right)) + 1;

    return k1;
}

AvlTree SingleRotateWithRight(Position k2) //右-右
{
    Position k1;
    k1 = k2->Right;
    k1->Left = k2;
    k2->Right = k1->Left;
    k2->Height = Max(Height(k2->Left), Height(k2->Right)) + 1;
    k1->Height = Max(Height(k1->Left), Height(k1->Right)) + 1;
    
    return k1;
}

AvlTree DoubleRotateWithLeft(Position k3) //左-右
{
    Position k1, k2;
    k1 = k3->Left;
    k2 = k1->Right;
    k3->Left = SingleRotateWithRight(k1);
    k2 = SingleRotateWithLeft(k3);  

    return k2;
}

AvlTree DoubleRotateWithRight(Position k3) //右-左
{
    Position k1, k2;
    k1 = k3->Right;
    k2 = k1->Left;
    k3->Right = SingleRotateWithLeft(k1);
    k2 = SingleRotateWithRight(k3);  

    return k2;
}

AvlTree Insert(ElementType X, AvlTree T)
{
    if (T == NULL) {
        T = (AvlTree)malloc(sizeof(struct AvlNode));
        if (T == NULL) {
            printf("Out of space!\n");
            return NULL;
        }
        T->Element = X;
        T->Left = NULL;
        T->Right = NULL;
        T->Height = 0;
    } else if (T->Element > X) {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2) { //不平衡点T
            if (X < T->Element) { //左-左
                T = SingleRotateWithLeft(T);
            } else { //左-右
                T = DoubleRotateWithLeft(T);
            }
        }
    } else if (T->Element < X) {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2) { //不平衡点T
            if (X > T->Element) { //右-右
                T = SingleRotateWithRight(T);
            } else { //右-左
                T = DoubleRotateWithRight(T);
            }
        }
    } 
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

AvlTree Delete(ElementType X, AvlTree T)
{

}

ElementType Retrieve(Position P)
{
    return P->Element;
}

int Height(Position P)
{
    if (P == NULL) {
        return -1;
    } else {
        return P->Height;
    }
}