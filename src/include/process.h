#pragma once

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int start_time;
    int end_time;
} Process;

typedef struct {
    Process **processes;
    int size;
    float ave_wait_time;
} ProcessList;

ProcessList* createProcessList(int num_process);
Process* createProcess(int pid, int arrival_time, int burst_time);
void shallowCopy(Process** dest, Process** src, int size);
void freeProcessList(ProcessList *pl);
void printProcessList(ProcessList *pl);

void sortArrival(Process **pl, int size);
void sortBurst(Process **pl, int size);
void sortPID(Process **pl, int size);
