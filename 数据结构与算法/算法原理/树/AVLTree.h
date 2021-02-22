#ifndef __AVLTree_H
#define __AVLTree_H
#include <stdio.h>
#include <stdlib.h>

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
#define ElementType int

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
ElementType Retrieve(Position P);
int Height(Position P);
AvlTree SingleRotateWithLeft(Position k2);
AvlTree SingleRotateWithRight(Position k2);
AvlTree DoubleRotateWithLeft(Position k3);
AvlTree DoubleRotateWithRight(Position k3);

#endif