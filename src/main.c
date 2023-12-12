#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "include/scheduling.h"

int main()
{
    uint64_t algo, num_processes, quantum;
    (void)!scanf("%" SCNu64 "%" SCNu64 "%" SCNu64, &algo, &num_processes, &quantum);

    if(algo != 3) {
        quantum = 1;
    }

    ProcessList *pl = createProcessList(num_processes);
    for(size_t i = 0; i < num_processes; i++) {
        uint64_t pid, arrival_time, burst_time = 0;
        (void)!scanf("%" SCNu64 "%" SCNu64 "%" SCNu64, &pid, &arrival_time, &burst_time);
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
    fprintf(stderr, "[BENCHMARK] CPU Time: %.4lf ms\n", elapsed * 1000);
#endif

    printProcessList(pl);
    printf("Average waiting time: %.1lf", pl->ave_wait_time);
    freeProcessList(pl);

    return 0;
}