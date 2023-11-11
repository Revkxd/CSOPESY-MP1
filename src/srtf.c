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
    Process **ready_table = malloc(sizeof(Process*) * pl->size);
    int *burst_table = malloc(sizeof(int) * pl->size);

    if (arrival_queue == NULL || ready_table == NULL || burst_table == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        Process *p = pl->processes[i];
        enqueue(arrival_queue, p);
        burst_table[p->pid - 1] = p->burst_time;
    }

    sortQueueArrival(arrival_queue);

    int preempt = 0;
    int active_processes = 0;
    Process *running = NULL;
    while (arrival_queue->size > 0 || active_processes > 0 ) {
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time <= time) {
            active_processes++;
            appendProcess(ready_table, active_processes, dequeue(arrival_queue));
            preempt = 1;
        }

        if (active_processes == 0) {
            time++;
            continue;
        }

        if (preempt == 1) {
            Process* min = findMinBurst(ready_table, active_processes);
            if (running == NULL || running->pid != min->pid)
                appendStartTime(min, time);
            if (running != NULL && running->pid != min->pid)
                appendEndTime(running, time);
            running = min;
            preempt = 0;
        }

        time++; 
        running->burst_time--;
        if (running->burst_time == 0) {
            appendEndTime(running, time);
            removeProcess(ready_table, active_processes, running);
            active_processes--;
            // compute wait time of completed process
            int turnaround = time - running->arrival_time;
            running->waiting_time = turnaround - burst_table[running->pid - 1];
            total_wait += running->waiting_time;
            running = NULL;
            preempt = 1;
        }
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    free(burst_table);
    free(ready_table);
    freeQueue(arrival_queue);
}