#ifndef _Stack_h
#define _Stack_h

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
#define ElementType int 

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

#endif