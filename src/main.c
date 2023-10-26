#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"


int main()
{
    int algo, num_processes, quantum;
    scanf("%d%d%d", &algo, &num_processes, &quantum);

    ProcessList *pl = createProcessList(num_processes);
    for(int i = 0; i < num_processes; i++) {
        int pid, arrival_time, burst_time = 0;
        scanf("%d%d%d", &pid, &arrival_time, &burst_time);
        pl->processes[i] = createProcess(pid, arrival_time, burst_time);
    }

    switch(algo) {
        case 0: FCFS(pl); break;
        case 1: SJF(pl); break;
        case 2: SRTF(pl); break;
        case 3: RR(pl, quantum); break;
        default: fprintf(stderr, "%s", "Error: Invalid Algorithm\n");
    }
    
    printProcessList(pl);
    printf("Average waiting time: %.1f\n", pl->ave_wait_time);
    freeProcessList(pl);

    return 0;
}