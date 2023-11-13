#include <stdio.h>
#include <stdlib.h>
#include "include/queue.h"

ProcessQueue *createQueue(size_t capacity)
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

void enqueue(ProcessQueue *pq, Process *p)
{
    if (pq->size == pq->capacity) {
        fprintf(stderr, "Error: Queue full\n");
        return;
    }
    pq->rear = (pq->rear + 1) % pq->capacity;
    pq->queue[pq->rear] = p;
    pq->size++;
}

Process* dequeue(ProcessQueue *pq)
{
    if(pq->size == 0) {
        fprintf(stderr, "Error: Queue empty\n");
        return NULL;
    }
    Process *p = pq->queue[pq->front];
    pq->front = (pq->front + 1) % pq->capacity;
    pq->size--;
    return p;
}

Process* peekQueue(ProcessQueue *pq)
{
    if (pq->size == 0) return NULL;
    return pq->queue[pq->front];
}