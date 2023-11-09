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

    for (int i = 0; i < ARR_MAX; i++) {
        p->start_time[i] = -1;
        p->end_time[i] = -1;
    }

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
        for (int j = 0; p->start_time[j] != -1 && j < ARR_MAX; j++)
            printf("start time: %d end time: %d | ", p->start_time[j], p->end_time[j]);
        printf("Waiting time: %d\n", p->waiting_time);
    }
}

void appendStartTime(Process *p, int start)
{
    int idx = 0;
    while(p->start_time[idx] != -1 && idx < ARR_MAX) {
        idx++;
    }
    p->start_time[idx] = start;
}

void appendEndTime(Process *p, int end)
{
    int idx = 0;
    while(p->end_time[idx] != -1 && idx < ARR_MAX) {
        idx++;
    }
    p->end_time[idx] = end;
}