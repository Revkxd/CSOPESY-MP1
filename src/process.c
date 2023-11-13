#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "include/scheduling.h"

ProcessList* createProcessList(size_t num_process)
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

Process* createProcess(uint32_t pid, uint32_t arrival_time, uint32_t burst_time)
{
    Process *p = malloc(sizeof(Process));

    if (p == NULL) {
        fprintf(stderr, "%s", "Error: Failed to allocate process\n");
        return NULL;
    }

    p->pid = pid;
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->remaining_burst = burst_time;
    p->waiting_time = 0;
    p->run_count = 0;

    return p;
}

void freeProcessList(ProcessList *pl)
{
    for (size_t i = 0; i < pl->size; i++) {
        free(pl->processes[i]);
    }
    free(pl->processes);
    free(pl);
}

void printProcessList(ProcessList *pl)
{
    for (size_t i = 0; i < pl->size; i++) {
        Process *p = pl->processes[i];
        printf("%" PRIu32 " ", p->pid);
        for (size_t j = 0; j < p->run_count; j++)
            printf("start time: %" PRIu32 " end time: %" PRIu32 " | ", p->start_time[j], p->end_time[j]);
        printf("Waiting time: %" PRIu32 "\n", p->waiting_time);
    }
}

void appendStartTime(Process *p, uint32_t start)
{
    if (p->run_count >= ARR_MAX) {
        fprintf(stderr, "Error: Index out of bounds with run_count=%zu\n", p->run_count);
        return;
    }
    p->start_time[p->run_count] = start;
}

void appendEndTime(Process *p, uint32_t end)
{
    if (p->run_count >= ARR_MAX) {
        fprintf(stderr, "Error: Index out of bounds with run_count=%zu\n", p->run_count);
        return;
    }
    p->end_time[p->run_count] = end;
    p->run_count++;
}