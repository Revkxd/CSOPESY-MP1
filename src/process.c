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
        fprintf(stderr, "%s", "Error: Failed to allocate process list\n");
        return NULL;
    }

    return pl;
}

Process* createProcess(int pid, int arrival_time, int burst_time)
{
    Process *p = malloc(sizeof(Process));

    if (p == NULL) {
        fprintf(stderr, "%s", "Error: Failed to allocate process\n");
        return NULL;
    }

    p->pid = pid;
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->waiting_time = 0;
    p->run_count = 0;

    return p;
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
        printf("%d ", p->pid);
        for (int j = 0; j < p->run_count; j++)
            printf("start time: %d end time: %d | ", p->start_time[j], p->end_time[j]);
        printf("Waiting time: %d\n", p->waiting_time);
    }
}

void appendStartTime(Process *p, int start)
{
    int idx = p->run_count;
    if (idx >= ARR_MAX) {
        fprintf(stderr, "Error: Index out of bounds with run_count=%d\n", idx);
        return;
    }
    p->start_time[idx] = start;
}

void appendEndTime(Process *p, int end)
{
    int idx = p->run_count;
    p->end_time[idx] = end;
    p->run_count++;
}

int findMinBurst(Process **table, int size)
{
    int min = 0;
    for (int i = 1; i < size; i++) {
        if (table[i] == NULL)
            break;
        if (table[i]->burst_time < table[min]->burst_time)
            min = i;
    }
    return min;
}

void insertProcess(Process **table, int size, int pos, Process *p)
{
    if (pos >= size) {
        fprintf(stderr, "Error: Index out of bounds inserting into table\n");
        return;
    }
    table[pos] = p;
}

void removeProcess(Process **table, int size, int pos)
{
    int idx = pos;
    while (idx < size) {
        if (table[idx] == NULL)
            break;
        table[idx] = table[idx + 1];
        idx++;
    }
}