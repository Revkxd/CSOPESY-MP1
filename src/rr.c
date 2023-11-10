#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

void RR(ProcessList *pl, int quantum)
{
    int time = 0;
    ProcessQueue *arrival_queue = createQueue(pl->size);
    ProcessQueue *ready_queue = createQueue(pl->size);
    int *burst_table = malloc(sizeof(int) * pl->size);

    if (arrival_queue == NULL || ready_queue == NULL || burst_table == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        Process *p = pl->processes[i];
        enqueue(arrival_queue, p);
        burst_table[p->pid - 1] = p->burst_time;
    }

    sortQueueArrival(arrival_queue);

    while (arrival_queue->size > 0 || ready_queue->size > 0) {
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time <= time)
            enqueue(ready_queue, dequeue(arrival_queue));

        if (ready_queue->size == 0) {
            time++;
            continue;
        }

        Process* running = dequeue(ready_queue);
        appendStartTime(running, time);
        if (burst_table[running->pid - 1] <= quantum) {
            time += burst_table[running->pid - 1];
            burst_table[running->pid - 1] = 0;
        } else {
            time += quantum;
            burst_table[running->pid - 1] -= quantum;
        }
        appendEndTime(running, time);

        // check for arrived processes before enqeueing the running process
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time < time)
            enqueue(ready_queue, dequeue(arrival_queue));
        if (burst_table[running->pid - 1] > 0)
            enqueue(ready_queue, running);
    }

    int total_wait = 0;
    for (int i = 0; i < pl->size; i++) {
        Process *p = pl->processes[i];
        int turnaround = getCompletion(p) - p->arrival_time;
        p->waiting_time = turnaround - p->burst_time;
        total_wait += p->waiting_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    free(burst_table);
    freeQueue(arrival_queue);
    freeQueue(ready_queue);
}