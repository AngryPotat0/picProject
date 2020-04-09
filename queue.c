#include"queue.h"
//#define __QUEUE_DEBUG__
#ifdef __QUEUE_DEBUG__
#include<stdio.h>
#endif
Queue* Create_Queue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    //queue->data = NULL;
    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;
    return queue;
}

int queue_Push(Queue* queue,elementType data)
{
#ifdef __QUEUE_DEBUG__
    printf("Into queue_push data is %d %d\n",data.y,data.x);
#endif
    QueuePtr p = (QueuePtr)malloc(sizeof(queueNode));
    if(!p)return 0;
    queue->length = queue->length + 1;
    p->data = data;
    p->Next = NULL;
    if(queue->length == 1)
    {
        queue->head = queue->tail = p;
#ifdef __QUEUE_DEBUG__
    printf("leave queue_push: now length is: %d\n",queue->length);
#endif
        return 1;
    }
    queue->tail->Next = p;
    queue->tail = p;
#ifdef __QUEUE_DEBUG__
    printf("leave queue_push: now length is: %d\n",queue->length);
#endif
    return 1;
}

elementType queue_Pop(Queue* queue)
{
#ifdef  __QUEUE_DEBUG__
    printf("Into queue_pop length is %d\n",queue->length);
#endif
    elementType badData = {-1,-1};
    if(queue->length == 0)return badData;
    queue->length = queue->length - 1;
    elementType data = (queue->head)->data;//something wrong is here
    //QueuePtr ppp = queue->head;
// #ifdef __QUEUE_DEBUG__
//     printf("works fine till now\n");
// #endif
    //elementType data = ppp->data;
    QueuePtr p = queue->head;
    queue->head = queue->head->Next;
    if(queue->length == 0)queue->head = queue->tail = NULL;
    free(p);
#ifdef  __QUEUE_DEBUG__
    printf("leave queue_pop,data is %d %d\n",data.y,data.x);
#endif
    return data;
}

int queue_IsEmpty(Queue* queue)
{
    if(queue->length)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
}

void destoryQueue(Queue* queue)
{
    QueuePtr p = queue->head;
    QueuePtr q;
    while(p != NULL)
    {
        q = p;
        p = p->Next;
        free(q);
    }
}
