#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

void SJF(ProcessList *pl)
{
    int time = 0;
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

    int process_arrived = 0;
    while (arrival_queue->size > 0 || ready_queue->size > 0) {
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time <= time) {
            enqueue(ready_queue, dequeue(arrival_queue));
            process_arrived = 1;
        }

        if (ready_queue->size == 0) {
            time++;
            continue;
        }

        if (process_arrived == 1) {
            sortQueueBurst(ready_queue);
            process_arrived = 0;
        }

        Process* running = dequeue(ready_queue);
        appendStartTime(running, time);
        appendEndTime(running, time + running->burst_time);
        running->waiting_time = time - running->arrival_time;
        time += running->burst_time;
    }

    int total_wait = 0;
    for (int i = 0; i < pl->size; i++) {
        total_wait += pl->processes[i]->waiting_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    freeQueue(arrival_queue);
    freeQueue(ready_queue);
}