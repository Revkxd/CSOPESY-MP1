#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/scheduling.h"

int main()
{
    int algo, num_processes, quantum;
    scanf("%d%d%d", &algo, &num_processes, &quantum);

    if(algo != 3) {
        quantum = 1;
    }

    ProcessList *pl = createProcessList(num_processes);
    for(int i = 0; i < num_processes; i++) {
        int pid, arrival_time, burst_time = 0;
        scanf("%d%d%d", &pid, &arrival_time, &burst_time);
        pl->processes[i] = createProcess(pid, arrival_time, burst_time);
    }

#ifdef BENCHMARK
    clock_t start = clock();
#endif

    switch(algo) {
        case 0: FCFS(pl); break;
        case 1: SJF(pl); break;
        case 2: SRTF(pl); break;
        case 3: RR(pl, quantum); break;
        default: fprintf(stderr, "%s", "Error: Invalid Algorithm\n");
    }

#ifdef BENCHMARK
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
#endif
    
#ifndef BENCHMARK
    printProcessList(pl);
    printf("Average waiting time: %.1f", pl->ave_wait_time);
#endif

#ifdef BENCHMARK
    printf("\n\n[BENCHMARK] CPU Time: %.4lf ms\n", elapsed * 1000);
#endif

    freeProcessList(pl);
    return 0;
}