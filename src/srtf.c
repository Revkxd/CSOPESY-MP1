#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

void SRTF(ProcessList *pl)
{
    int time = 0;
    int total_wait = 0;
    ProcessQueue *arrival_queue = createQueue(pl->size);
    ProcessQueue *process_queue = createQueue(pl->size);

    if (arrival_queue == NULL || process_queue == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        enqueue(arrival_queue, pl->processes[i]);
    }

    sortArrival(arrival_queue->queue, arrival_queue->capacity);

    int preempt = 0;
    while (arrival_queue->size > 0 || process_queue->size > 0 ) {
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time <= time) {
            enqueue(process_queue, dequeue(arrival_queue));
            preempt = 1;
        }

        if (process_queue->size == 0) {
            time++;
            continue;
        }

        if (preempt == 1) {
            sortQueueBurst(process_queue);
            preempt = 0;
        }

        Process* running = peek(process_queue);
        if (running->start_time == -1)
            running->start_time = time;

        running->burst_time--;

        int idx = process_queue->front;
        int rear = (process_queue->rear + 1) % process_queue->capacity;
        while (idx != rear) {
            if (running->pid != process_queue->queue[idx]->pid) {
                process_queue->queue[idx]->waiting_time++;
                total_wait++;
            }
            idx = (idx + 1) % process_queue->capacity;
        }

        if (running->burst_time == 0) {
            running->end_time = time + 1;
            dequeue(process_queue);
        }

        time++;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    freeQueue(arrival_queue);
    freeQueue(process_queue);
}