#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"


int main()
{
    int algo, num_processes, quantum;
    scanf("%d%d%d", &algo, &num_processes, &quantum);

    ProcessQueue pq = createProcessQueue(num_processes);
    for(int i = 0; i < num_processes; i++) {
        Process p;
        scanf("%d%d%d", &p.pid, &p.arrival_time, &p.burst_time);
        pq.processes[i] = p;
    }

    switch(algo) {
        case 0: FCFS(pq); break;
        case 1: SJF(pq); break;
        case 2: SRTF(pq); break;
        case 3: RR(pq, quantum); break;
        default: fprintf(stderr, "%s", "Error: Invalid Algorithm");
    }

    printProcessQueue(pq);
    freeProcessQueue(pq);

    return 0;
}