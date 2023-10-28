#include <stdio.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

void SJF(ProcessList *pl)
{
    int time = 0;
    ProcessQueue *arrival_queue = createQueue(pl->size);
    ProcessQueue *wait_queue = createQueue(pl->size);

    if (arrival_queue == NULL || wait_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        enqueue(arrival_queue, pl->processes[i]);
    }

    sortArrival(arrival_queue->queue, arrival_queue->capacity);

    while (arrival_queue->size > 0 || wait_queue->size > 0) {
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time <= time)
            enqueue(wait_queue, dequeue(arrival_queue));

        if (wait_queue->size == 0) {
            time++;
            continue;
        }

        sortQueueBurst(wait_queue);
        Process* running = dequeue(wait_queue);
        running->start_time = time;
        running->end_time = time + running->burst_time;
        running->waiting_time = time - running->arrival_time;
        time += running->burst_time;
    }

    int total_wait = 0;
    for (int i = 0; i < pl->size; i++) {
        total_wait += pl->processes[i]->waiting_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    freeQueue(arrival_queue);
    freeQueue(wait_queue);
}