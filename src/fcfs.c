#include "include/scheduling.h"

void FCFS(ProcessQueue pq)
{
    sortArrival(pq);

    // first arrived process has no wait time
    Process *first = &pq.processes[0];
    first->start_time = first->arrival_time;
    first->end_time = first->start_time + first->burst_time;
    first->waiting_time = 0;

    for (int i = 1; i < pq.size; i++) {
        Process *curr = &pq.processes[i];
        Process *prev = &pq.processes[i - 1];
        curr->start_time = prev->end_time;
        curr->end_time = curr->start_time + curr->burst_time;
        curr->waiting_time = curr->end_time - curr->arrival_time - curr->burst_time;
    }

    sortPID(pq);
}