#ifndef _STACK
#define _STACK
#include<stdlib.h>
#include"bmpStruct.h"

#ifndef ELEMENTTYPE
#define ELEMENTTYPE

typedef struct{
    int x;
    int y;
}elementType;
#endif

struct StackNode {
    elementType data;
    struct StackNode* Next;
};
typedef struct StackNode StackNode;
typedef StackNode *StackPtr;
typedef StackNode *Stack;

StackPtr CreateStack(elementType data);
StackPtr stack_Push(StackPtr stack,elementType data);
elementType stack_Top(StackPtr stack);
StackPtr stack_pop(StackPtr stack);
int stack_Length(StackPtr stack);
int stack_IsEmpty(Stack stack);
void destroyStack(StackPtr stack);

#endif