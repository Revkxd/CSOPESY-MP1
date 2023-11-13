#include <stdio.h>
#include <inttypes.h>
#include "include/scheduling.h"
#include "include/heap.h"

void SRTF(ProcessList *pl)
{
    uint64_t time = 0;
    uint64_t total_wait = 0;
    ProcessHeap *arrival_queue = createHeap(pl->size, ARRIVAL);
    ProcessHeap *ready_queue = createHeap(pl->size, BURST);

    if (arrival_queue == NULL || ready_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (size_t i = 0; i < pl->size; i++) {
        insertHeap(arrival_queue, pl->processes[i]);
    }

    int preempt = 0;
    Process *running = NULL;
    while (arrival_queue->size > 0 || ready_queue->size > 0 ) {
        while (peekHeap(arrival_queue) != NULL && peekHeap(arrival_queue)->arrival_time <= time) {
            insertHeap(ready_queue, extractMin(arrival_queue));
            preempt = 1;
        }

        if (ready_queue->size == 0) {
            time = peekHeap(arrival_queue)->arrival_time;
            continue;
        }

        if (preempt == 1) {
            Process *min = peekHeap(ready_queue);
            if (running == NULL || running->pid != min->pid)
                appendStartTime(min, time);
            if (running != NULL && running->pid != min->pid)
                appendEndTime(running, time);
            running = min;
            preempt = 0;
        }

        time++; 
        running->remaining_burst--;
        if (running->remaining_burst == 0) {
            running = NULL;
            preempt = 1;
            // compute wait time of completed process
            Process *completed = extractMin(ready_queue);
            appendEndTime(completed, time);
            int turnaround = time - completed->arrival_time;
            completed->waiting_time = turnaround - completed->burst_time;
            total_wait += completed->waiting_time;
        }
    }

    pl->ave_wait_time = (double)total_wait / (double)pl->size;
    freeHeap(ready_queue);
    freeHeap(arrival_queue);
}