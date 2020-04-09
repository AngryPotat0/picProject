#ifndef _QUEUE
#define _QUEUE
#include<stdlib.h>
#include"bmpStruct.h"
#ifndef ELEMENTTYPE
#define ELEMENTTYPE
typedef struct{
    int x;
    int y;
}elementType;
#endif

struct queueNode{
    elementType data;
    struct queueNode* Next;
};
typedef struct queueNode queueNode;
typedef queueNode *QueuePtr;
typedef struct{
    //QueuePtr data;
    QueuePtr head;
    QueuePtr tail;
    int length;
}Queue;
Queue* Create_Queue();
int queue_Push(Queue* queue,elementType data);
elementType queue_Pop(Queue* queue);
int queue_IsEmpty(Queue* queue);
void destoryQueue(Queue* queue);




#endif