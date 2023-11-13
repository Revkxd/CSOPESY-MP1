#include <stdio.h>
#include <stdlib.h>
#include "include/heap.h"

int cmpArrivalHeap(const Process *a, const Process *b)
{
    if (a->arrival_time == b->arrival_time)
        return a->pid - b->pid;
    return a->arrival_time - b->arrival_time;
}

int cmpBurstHeap(const Process *a, const Process *b)
{
    if (a->remaining_burst == b->remaining_burst)
        return a->pid - b->pid;
    return a->remaining_burst - b->remaining_burst;
}

ProcessHeap* createHeap(size_t capacity, int heap_type)
{
    ProcessHeap *ph = malloc(sizeof(ProcessHeap));
    if (ph == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate queue\n");
        return NULL;
    }

    ph->heap = malloc(sizeof(Process*) * capacity);
    if (ph->heap == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate queue\n");
        return NULL;
    }

    ph->capacity = capacity;
    ph->size = 0;

    if (heap_type == ARRIVAL) {
        ph->cmp = cmpArrivalHeap;
    } else if (heap_type == BURST) {
        ph->cmp = cmpBurstHeap;
    } else {
        fprintf(stderr, "Error: Invalid heap type\n");
        return NULL;
    }
    
    return ph;
}

void freeHeap(ProcessHeap *ph)
{
    free(ph->heap);
    free(ph);
}

void swap(Process **array, size_t a, size_t b)
{
    Process *temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void minHeapify(ProcessHeap *ph, size_t index)
{
    size_t min = index;
    size_t left = index * 2 + 1;
    size_t right = index * 2 + 2;

    if (left < ph->size && ph->cmp(ph->heap[left], ph->heap[min]) < 0)
        min = left;

    if (right < ph->size && ph->cmp(ph->heap[right], ph->heap[min]) < 0)
        min = right;

    if (min != index) {
        swap(ph->heap, min, index);
        minHeapify(ph, min);
    }
}

void insertHeap(ProcessHeap *ph, Process *p)
{
    if (ph->size == ph->capacity) {
        fprintf(stderr, "Error: Called insertHeap on full heap\n");
        return;
    }
    ph->heap[ph->size] = p;
    ph->size++;

    size_t idx = ph->size - 1;
    while (idx != 0 && ph->cmp(ph->heap[idx], ph->heap[(idx - 1) / 2]) < 0) {
        swap(ph->heap, idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

Process* extractMin(ProcessHeap *ph)
{
    if (ph->size == 0) {
        fprintf(stderr, "Error: Called extractMin on empty heap\n");
        return NULL;
    }
    Process *p = ph->heap[0];
    ph->heap[0] = ph->heap[--ph->size];
    minHeapify(ph, 0);
    return p;
}

Process* peekHeap(ProcessHeap *ph)
{
    if (ph->size == 0)
        return NULL;
    return ph->heap[0];
}