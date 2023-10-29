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
void freeProcessList(ProcessList *pl);
void printProcessList(ProcessList *pl);