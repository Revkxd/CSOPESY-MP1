#include <stdio.h>
#include <inttypes.h>
#include "include/scheduling.h"
#include "include/heap.h"
#include "include/queue.h"

void RR(ProcessList *pl, size_t quantum)
{
    uint64_t time = 0;
    uint64_t total_wait = 0;
    ProcessHeap *arrival_queue = createHeap(pl->size, ARRIVAL);
    ProcessQueue *ready_queue = createQueue(pl->size);

    if (arrival_queue == NULL || ready_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (size_t i = 0; i < pl->size; i++) {
        insertHeap(arrival_queue, pl->processes[i]);
    }

    while (arrival_queue->size > 0 || ready_queue->size > 0) {
        while (peekHeap(arrival_queue) != NULL && peekHeap(arrival_queue)->arrival_time <= time)
            enqueue(ready_queue, extractMin(arrival_queue));

        if (ready_queue->size == 0) {
            time = peekHeap(arrival_queue)->arrival_time;
            continue;
        }

        Process* running = dequeue(ready_queue);
        appendStartTime(running, time);
        if (running->remaining_burst <= quantum) {
            time += running->remaining_burst;
            running->remaining_burst = 0;
            // compute wait time of completed process
            int turnaround = time - running->arrival_time;
            running->waiting_time = turnaround - running->burst_time;
            total_wait += running->waiting_time;
        } else {
            time += quantum;
            running->remaining_burst -= quantum;
        }
        appendEndTime(running, time);

        // check for arrived processes before enqeueing the running process
        while (peekHeap(arrival_queue) != NULL && peekHeap(arrival_queue)->arrival_time < time)
            enqueue(ready_queue, extractMin(arrival_queue));
        if (running->remaining_burst > 0)
            enqueue(ready_queue, running);
    }

    pl->ave_wait_time = (double)total_wait / (double)pl->size;
    freeHeap(arrival_queue);
    freeQueue(ready_queue);
}