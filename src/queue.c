#include <stdio.h>
#include <stdlib.h>
#include "include/queue.h"

ProcessQueue *createQueue(int capacity)
{
    ProcessQueue *q = malloc(sizeof(ProcessQueue));
    if (q == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate queue\n");
        return NULL;
    }

    q->queue = malloc(sizeof(Process*) * capacity);
    if (q->queue == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate queue\n");
        return NULL;
    }

    q->capacity = capacity;
    q->size = 0;
    q->rear = -1;
    q->front = 0;
    
    return q;
}

void freeQueue(ProcessQueue *pq)
{
    free(pq->queue);
    free(pq);
}

int isFull(ProcessQueue *pq)
{
    return (pq->size == pq->capacity);
}

int isEmpty(ProcessQueue *pq)
{
    return (pq->size == 0);
}

void enqueue(ProcessQueue *pq, Process *p)
{
    if (isFull(pq)) {
        fprintf(stderr, "Error: Queue full\n");
        return;
    }
    pq->rear = (pq->rear + 1) % pq->capacity;
    pq->queue[pq->rear] = p;
    pq->size++;
}

Process* dequeue(ProcessQueue *pq)
{
    if(isEmpty(pq)) {
        fprintf(stderr, "Error: Queue empty\n");
        return NULL;
    }
    Process *p = pq->queue[pq->front];
    pq->queue[pq->front] = NULL;
    pq->front = (pq->front + 1) % pq->capacity;
    pq->size--;

    return p;
}

Process* peek(ProcessQueue *pq)
{
    if (isEmpty(pq)) return NULL;
    return pq->queue[pq->front];
}

void sortQueueBurst(ProcessQueue* pq)
{
    if (isEmpty(pq)) return;

    Process **temp = malloc(sizeof(Process*) * pq->capacity);
    if (temp == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate queue\n");
        return;
    }

    int count = 0;
    while (!isEmpty(pq)) {
        temp[count] = dequeue(pq);
        count++;
    }

    qsort(temp, count, sizeof(Process*), cmpBurst);

    for (int i = 0; i < count; i++)
        enqueue(pq, temp[i]);

    free(temp);
}