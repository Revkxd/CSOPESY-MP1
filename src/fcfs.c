#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"

void FCFS(ProcessList *pl)
{
    Process** sorted_arrival = malloc(sizeof(Process*) * pl->size);

    if (sorted_arrival == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    shallowCopy(sorted_arrival, pl->processes, pl->size);
    sortArrival(sorted_arrival, pl->size);

    // first arrived process has no wait time
    Process *first = sorted_arrival[0];
    first->start_time = first->arrival_time;
    first->end_time = first->start_time + first->burst_time;
    first->waiting_time = 0;

    int total_wait = 0;
    for (int i = 1; i < pl->size; i++) {
        Process *curr = sorted_arrival[i];
        Process *prev = sorted_arrival[i - 1];
        curr->start_time = prev->end_time;
        curr->end_time = curr->start_time + curr->burst_time;
        curr->waiting_time = curr->end_time - curr->arrival_time - curr->burst_time;
        total_wait += curr->waiting_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;
    free(sorted_arrival);
}