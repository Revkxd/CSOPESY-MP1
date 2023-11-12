#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/heap.h"

void SJF(ProcessList *pl)
{
    int time = 0;
    int total_wait = 0;
    ProcessHeap *arrival_queue = createHeap(pl->size, ARRIVAL);
    ProcessHeap *ready_queue = createHeap(pl->size, BURST);

    if (arrival_queue == NULL || ready_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        insertHeap(arrival_queue, pl->processes[i]);
    }

    while (arrival_queue->size > 0 || ready_queue->size > 0) {
        while (peekHeap(arrival_queue) != NULL && peekHeap(arrival_queue)->arrival_time <= time) {
            insertHeap(ready_queue, extractMin(arrival_queue));
        }

        if (ready_queue->size == 0) {
            time = peekHeap(arrival_queue)->arrival_time;
            continue;
        }

        Process* running = extractMin(ready_queue);
        appendStartTime(running, time);
        appendEndTime(running, time + running->burst_time);
        running->remaining_burst = 0;
        // compute wait time of completed process
        running->waiting_time = time - running->arrival_time;
        total_wait += running->waiting_time;
        time += running->burst_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    freeHeap(ready_queue);
    freeHeap(arrival_queue);
}