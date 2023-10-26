#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"

ProcessList* createProcessList(int num_process)
{
    ProcessList *pl = malloc(sizeof(ProcessList));
    pl->processes = malloc(sizeof(Process*) * num_process);
    pl->size = num_process;
    pl->ave_wait_time = 0;

    if (pl == NULL || pl->processes == NULL) {
        fprintf(stderr, "%s", "Error: Failed to allocate process list");
        return NULL;
    }

    return pl;
}

Process* createProcess(int pid, int arrival_time, int burst_time)
{
    Process *p = malloc(sizeof(Process));

    if (p == NULL) {
        fprintf(stderr, "%s", "Error: Failed to allocate process");
        return NULL;
    }

    p->pid = pid;
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->start_time = 0;
    p->end_time = 0;
    p->waiting_time = 0;

    return p;
}

void shallowCopy(Process** dest, Process** src, int size)
{
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void freeProcessList(ProcessList *pl)
{
    for (int i = 0; i < pl->size; i++) {
        free(pl->processes[i]);
    }
    free(pl->processes);
    free(pl);
}

void printProcessList(ProcessList *pl)
{
    for (int i = 0; i < pl->size; i++) {
        Process *p = pl->processes[i];
        printf("%d start time: %d end time: %d | Waiting time: %d\n", 
            p->pid,
            p->start_time,
            p->end_time,
            p->waiting_time
        );
    }
}

int cmpArrival(const void *a, const void *b)
{
    Process *p_a = *(Process**)a;
    Process *p_b = *(Process**)b;
    return p_a->arrival_time - p_b->arrival_time;
}

int cmpPID(const void *a, const void *b)
{
    Process *p_a = *(Process**)a;
    Process *p_b = *(Process**)b;
    return p_a->pid - p_b->pid;
}

int cmpBurst(const void *a, const void *b)
{
    Process *p_a = *(Process**)a;
    Process *p_b = *(Process**)b;
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
