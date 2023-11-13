#pragma once

#include "process.h"

typedef struct {
    Process **queue;
    size_t capacity;
    size_t front;
    size_t rear;
    size_t size;
} ProcessQueue;

ProcessQueue *createQueue(size_t capacity);
void freeQueue(ProcessQueue *pq);
void enqueue(ProcessQueue *pq, Process *p);
Process* dequeue(ProcessQueue *pq);
Process* peekQueue(ProcessQueue *pq);