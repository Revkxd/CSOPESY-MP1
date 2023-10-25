#include <stdio.h>
#include <stdlib.h>
#include "include/scheduling.h"


int main()
{
    int algo, num_processes, quantum;
    scanf("%d %d %d", &algo, &num_processes, &quantum);

    //value of X is not the Round-Robin algorithm, this value (quantum Z) must be set to 1 but ignored.
    if(algo != 3) {
        quantum = 1;
    }
    if(num_processes < 3 || num_processes > 100) {
        printf("Not in scope\n");
        return 0;
    }

    // num_processes rows for total number of processes
    // 3 columns for A B C (process id, arrival_time, burst time)
    // read the specs if hindi magets nakasulat
    Process processes[num_processes]; 
    for(int i = 0; i < num_processes; i++) {
        scanf("%d %d %d", &processes[i].process_id, &processes[i].arrival_time, &processes[i].burst_time);
    }

    switch(algo) {
        case 0: FCFS(processes); break;
        case 1: SJF(processes); break;
        case 2: SRTF(processes); break;
        case 3: RR(processes, quantum);
    }

    return 0;
}