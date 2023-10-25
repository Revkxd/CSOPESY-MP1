#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"

ProcessQueue createProcessQueue(int num_process)
{
    ProcessQueue pq = {
        num_process,
        malloc(sizeof(Process) * num_process),
        calloc(num_process, sizeof(int)),
        calloc(num_process, sizeof(int))
    };

    if (pq.processes == NULL || pq.arrival == NULL || pq.burst == NULL) {
        fprintf(stderr, "%s", "Error: Failed to allocate process queue");
    }

    return pq;
}

void printProcessQueue(ProcessQueue pq)
{
    for (int i = 0; i < pq.size; i++) {
        Process p = pq.processes[i];
        printf("%d start time: %d end time: %d | Waiting time: %d\n", 
            p.pid,
            p.start_time,
            p.end_time,
            p.waiting_time
        );
    }
}

void freeProcessQueue(ProcessQueue pq)
{
    free(pq.processes);
    free(pq.arrival);
    free(pq.burst);
}