#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

void RR(ProcessList *pl, int quantum)
{
    int time = 0;
    int total_wait = 0;
    ProcessQueue *arrival_queue = createQueue(pl->size);
    ProcessQueue *ready_queue = createQueue(pl->size);

    if (arrival_queue == NULL || ready_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        enqueue(arrival_queue, pl->processes[i]);
    }

    sortQueueArrival(arrival_queue);

    while (arrival_queue->size > 0 || ready_queue->size > 0) {
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time <= time)
            enqueue(ready_queue, dequeue(arrival_queue));

        if (ready_queue->size == 0) {
            time = peek(arrival_queue)->arrival_time;
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
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time < time)
            enqueue(ready_queue, dequeue(arrival_queue));
        if (running->remaining_burst > 0)
            enqueue(ready_queue, running);
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    freeQueue(arrival_queue);
    freeQueue(ready_queue);
}