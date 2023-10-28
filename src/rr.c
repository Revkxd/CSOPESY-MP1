#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

void RR(ProcessList *pl, int quantum)
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

        Process* running = dequeue(wait_queue);
        for (int i = 1; i <= quantum; i++) {
            if (running -> burst_time == 0) {
                break;
            }
            running->waiting_time += time - running->end_time;
            running->burst_time -= 1;
            time++;
            
            if(peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time == time)
                enqueue(wait_queue, dequeue(arrival_queue));
        }
        enqueue(wait_queue, running);
    }
}