#include <stdio.h>
#include <stdlib.h>
#include "include/sort.h"

int cmpArrival(const void *a, const void *b)
{
    Process *p_a = *(Process**)a;
    Process *p_b = *(Process**)b;

    if (p_a == NULL && p_b == NULL) return 0;
    if (p_a == NULL) return 1;
    if (p_b == NULL) return -1;
    // fix for windows qsort implementation not being in-place. L windows, W linux
    if (p_a->arrival_time - p_b->arrival_time == 0) return p_a->pid - p_b->pid;
    return p_a->arrival_time - p_b->arrival_time;
}

int cmpPID(const void *a, const void *b)
{
    Process *p_a = *(Process**)a;
    Process *p_b = *(Process**)b;

    if (p_a == NULL && p_b == NULL) return 0;
    if (p_a == NULL) return 1;
    if (p_b == NULL) return -1;
    return p_a->pid - p_b->pid;
}

int cmpBurst(const void *a, const void *b)
{
    Process *p_a = *(Process**)a;
    Process *p_b = *(Process**)b;

    if (p_a == NULL && p_b == NULL) return 0;
    if (p_a == NULL) return 1;
    if (p_b == NULL) return -1;
    // fix for windows qsort implementation not being in-place. L windows, W linux
    if (p_a->burst_time - p_b->burst_time == 0) return p_a->pid - p_b->pid;
    return p_a->burst_time - p_b->burst_time;
}

void sortArrival(Process **p, int size)
{
    qsort(p, size, sizeof(Process*), cmpArrival);
}

void sortPID(Process **p, int size)
{
    qsort(p, size, sizeof(Process*), cmpPID);
}

void sortBurst(Process **p, int size)
{
    qsort(p, size, sizeof(Process*), cmpBurst);
}

void sortQueueBurst(ProcessQueue* pq)
{
    if (pq->size == 0) return;

    Process **temp = malloc(sizeof(Process*) * pq->capacity);
    if (temp == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate queue\n");
        return;
    }

    int count = 0;
    while (pq->size > 0) {
        temp[count] = dequeue(pq);
        count++;
    }

    sortBurst(temp, count);
    for (int i = 0; i < count; i++)
        enqueue(pq, temp[i]);

    free(temp);
}