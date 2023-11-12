#pragma once

#include "process.h"

typedef struct {
    Process **queue;
    int capacity;
    int front;
    int rear;
    int size;
} ProcessQueue;

ProcessQueue *createQueue(int capacity);
void freeQueue(ProcessQueue *pq);
void enqueue(ProcessQueue *pq, Process *p);
Process* dequeue(ProcessQueue *pq);
Process* peekQueue(ProcessQueue *pq);