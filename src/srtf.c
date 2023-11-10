#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"
#include "include/queue.h"
#include "include/sort.h"

Process* findMinBurst(Process **table, int size)
{
    int idx = 1;
    Process *min = table[0];
    while (table[idx] != NULL && idx < size) {
        if (table[idx]->burst_time < min->burst_time)
            min = table[idx];
        idx++;
    }
    return min;
}

void insertProcess(Process **table, int size, Process *p)
{
    int idx = 0;
    while (table[idx] != NULL && idx < size)
        idx++;
    table[idx] = p;
}

void removeProcess(Process **table, int size, Process *p)
{
    int idx = -1;
    for (int i = 0; i < size && table[i] != NULL; i++) {
        if (p->pid == table[i]->pid) {
            idx = i;
            break; 
        }
    }
    while (idx != -1 && table[idx] != NULL && idx < size) {
        table[idx] = table[idx + 1];
        idx++;
    }
}

void SRTF(ProcessList *pl)
{
    int time = 0;
    ProcessQueue *arrival_queue = createQueue(pl->size);
    Process **ready_table = calloc(ARR_MAX, sizeof(Process*));
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
            insertProcess(ready_table, ARR_MAX, dequeue(arrival_queue));
            active_processes++;
            preempt = 1;
        }

        if (active_processes == 0) {
            time++;
            continue;
        }

        if (preempt == 1) {
            Process* minBurst = findMinBurst(ready_table, ARR_MAX);
            if (running == NULL || running->pid != minBurst->pid)
                appendStartTime(minBurst, time);
            if (running != NULL && running->pid != minBurst->pid)
                appendEndTime(running, time);
            running = minBurst;
            preempt = 0;
        }

        time++; 
        running->burst_time--;
        if (running->burst_time == 0) {
            appendEndTime(running, time);
            removeProcess(ready_table, ARR_MAX, running);
            running = NULL;
            active_processes--;
            preempt = 1;
        }
    }

    int total_wait = 0;
    for (int i = 0; i < pl->size; i++) {
        Process *p = pl->processes[i];
        int turnaround = getCompletion(p) - p->arrival_time;
        p->waiting_time = turnaround - burst_table[p->pid - 1];
        total_wait += p->waiting_time;
    }

    pl->ave_wait_time = (float)total_wait / (float)pl->size;

    free(burst_table);
    free(ready_table);
    freeQueue(arrival_queue);
}