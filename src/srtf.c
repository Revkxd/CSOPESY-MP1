#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/heap.h"

void SRTF(ProcessList *pl)
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
            appendEndTime(running, time);
            extractMin(ready_queue);
            preempt = 1;
            // compute wait time of completed process
            int turnaround = time - running->arrival_time;
            running->waiting_time = turnaround - running->burst_time;
            total_wait += running->waiting_time;
            running = NULL;
        }
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;
    freeHeap(ready_queue);
    freeHeap(arrival_queue);
}