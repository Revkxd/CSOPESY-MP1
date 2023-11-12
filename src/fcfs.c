#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/sort.h"

void FCFS(ProcessList *pl)
{
    Process** sorted_arrival = malloc(sizeof(Process*) * pl->size);

    if (sorted_arrival == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        sorted_arrival[i] = pl->processes[i];
    }

    sortArrival(sorted_arrival, pl->size);

    // first arrived process has no wait time
    Process *first = sorted_arrival[0];
    appendStartTime(first, first->arrival_time);
    appendEndTime(first, first->start_time[0] + first->burst_time);
    first->remaining_burst = 0;
    first->waiting_time = 0;

    int total_wait = 0;
    for (int i = 1; i < pl->size; i++) {
        Process *curr = sorted_arrival[i];
        Process *prev = sorted_arrival[i - 1];
        appendStartTime(curr, prev->end_time[0]);
        appendEndTime(curr, curr->start_time[0] + curr->burst_time);
        curr->remaining_burst = 0;
        curr->waiting_time = curr->end_time[0] - curr->arrival_time - curr->burst_time;
        total_wait += curr->waiting_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;
    free(sorted_arrival);
}