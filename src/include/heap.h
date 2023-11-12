#pragma once

#define ARRIVAL 0
#define BURST 1
#include "process.h"

typedef struct {
    Process **heap;
    int size;
    int capacity;
    int (*cmp)(const Process*,const Process*);
} ProcessHeap;

ProcessHeap* createHeap(int capacity, int heap_type);
void freeHeap(ProcessHeap *ph);
void insertHeap(ProcessHeap *ph, Process *p);
Process* extractMin(ProcessHeap *ph);
Process* peekHeap(ProcessHeap *ph);