#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

void SJF(ProcessList *pl)
{
    int time = 0;
    int total_wait = 0;
    ProcessQueue *arrival_queue = createQueue(pl->size);
    Process **ready_table = calloc(pl->size, sizeof(Process*));

    if (arrival_queue == NULL || ready_table == NULL) {
        fprintf(stderr, "%s", "Error: Unable to allocate\n");
        return;
    }

    for (int i = 0; i < pl->size; i++) {
        enqueue(arrival_queue, pl->processes[i]);
    }

    sortQueueArrival(arrival_queue);

    int active_processes = 0;
    while (arrival_queue->size > 0 || active_processes > 0) {
        while (peek(arrival_queue) != NULL && peek(arrival_queue)->arrival_time <= time) {
            insertProcess(ready_table, pl->size, active_processes, dequeue(arrival_queue));
            active_processes++;
        }

        if (active_processes == 0) {
            time = peek(arrival_queue)->arrival_time;
            continue;
        }

        int minIdx = findMinBurst(ready_table, active_processes);
        Process* running = ready_table[minIdx];
        appendStartTime(running, time);
        appendEndTime(running, time + running->burst_time);
        removeProcess(ready_table, pl->size, minIdx);
        running->remaining_burst = 0;
        active_processes--;
        // compute wait time of completed process
        running->waiting_time = time - running->arrival_time;
        total_wait += running->waiting_time;
        time += running->burst_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    free(ready_table);
    freeQueue(arrival_queue);
}