#include"stack.h"
StackPtr CreateStack(elementType data)
{
    StackPtr s = (StackPtr)malloc(sizeof(StackNode));
    s->data = data;
    s->Next = NULL;
    return s;
}

StackPtr stack_Push(StackPtr stack,elementType data)
{
    //ds.stackLength += 1;
    StackPtr s = (StackPtr)malloc(sizeof(StackNode));
    if(s == NULL){/*ds.stackFull = 1;*/ return stack;}
    s->data = data;
    s->Next = stack;
    return s;
}

elementType stack_Top(StackPtr stack)
{
    elementType badData = {-1,-1};
    if(!stack)return badData;
    return stack->data;
}

StackPtr stack_pop(StackPtr stack)
{
    if(!stack)return NULL;
    //ds.stackLength -= 1;
    StackPtr s = stack->Next;
    free(stack);
    return s;
}
int stack_Length(StackPtr stack)
{
    const StackNode* s = stack;
    int count = 0;
    for(;s;count++)s = s->Next;
    return count;
}

int stack_IsEmpty(Stack stack)
{
    if(stack)return 1;
    return 0;
}

void destroyStack(StackPtr stack)
{
    while (stack)
    {
        stack = stack_pop(stack);
    }
    
}
