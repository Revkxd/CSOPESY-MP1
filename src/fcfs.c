#include <stdio.h>
#include <inttypes.h>
#include "include/scheduling.h"
#include "include/heap.h"

void FCFS(ProcessList *pl)
{
    ProcessHeap *arrival_queue = createHeap(pl->size, ARRIVAL);
    if (arrival_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (size_t i = 0; i < pl->size; i++) {
        insertHeap(arrival_queue, pl->processes[i]);
    }

    Process *prev;
    Process *curr;
    uint64_t total_wait = 0;
    for (size_t i = 0; i < pl->size; i++) {
        // first arrived process has no wait time
        if (i == 0) {
            prev = extractMin(arrival_queue);
            appendStartTime(prev, prev->arrival_time);
            appendEndTime(prev, prev->start_time[0] + prev->burst_time);
            prev->remaining_burst = 0;
            prev->waiting_time = 0;
            continue;
        }
        curr = extractMin(arrival_queue);
        appendStartTime(curr, prev->end_time[0]);
        appendEndTime(curr, curr->start_time[0] + curr->burst_time);
        curr->remaining_burst = 0;
        curr->waiting_time = curr->end_time[0] - curr->arrival_time - curr->burst_time;
        total_wait += curr->waiting_time;
        prev = curr;
    }

    pl->ave_wait_time = (double)total_wait / (double)pl->size;
    freeHeap(arrival_queue);
}