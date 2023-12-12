#include <stdio.h>
#include <inttypes.h>
#include "include/scheduling.h"
#include "include/heap.h"

void SJF(ProcessList *pl)
{
    uint64_t time = 0;
    ProcessHeap *arrival_queue = createHeap(pl->size, ARRIVAL);
    ProcessHeap *ready_queue = createHeap(pl->size, BURST);

    if (arrival_queue == NULL || ready_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (size_t i = 0; i < pl->size; i++) {
        insertHeap(arrival_queue, pl->processes[i]);
    }

    size_t finished = 0;
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
        pl->ave_wait_time = computeStreamAve(pl->ave_wait_time, running->waiting_time, finished++);
        time += running->burst_time;
    }

    freeHeap(ready_queue);
    freeHeap(arrival_queue);
}