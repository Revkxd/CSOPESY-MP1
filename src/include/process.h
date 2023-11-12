#pragma once

#define ARR_MAX 512

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int start_time[ARR_MAX];
    int end_time[ARR_MAX];
    int run_count;
} Process;

Process* createProcess(int pid, int arrival_time, int burst_time);
void appendStartTime(Process *p, int start);
void appendEndTime(Process *p, int end);
int findMinBurst(Process **table, int size);
void insertProcess(Process **table, int size, int pos, Process *p);
void removeProcess(Process **table, int size, int pos);

typedef struct {
    Process **processes;
    int size;
    float ave_wait_time;
} ProcessList;

ProcessList* createProcessList(int num_process);
void freeProcessList(ProcessList *pl);
void printProcessList(ProcessList *pl);