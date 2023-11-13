#pragma once

#define ARRIVAL 0
#define BURST 1
#include "process.h"

typedef struct {
    Process **heap;
    size_t size;
    size_t capacity;
    int (*cmp)(const Process*,const Process*);
} ProcessHeap;

ProcessHeap* createHeap(size_t capacity, int heap_type);
void freeHeap(ProcessHeap *ph);
void insertHeap(ProcessHeap *ph, Process *p);
Process* extractMin(ProcessHeap *ph);
Process* peekHeap(ProcessHeap *ph);