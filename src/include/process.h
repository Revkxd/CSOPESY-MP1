#pragma once

#define ARR_MAX 64

typedef struct {
    unsigned int pid;
    unsigned int arrival_time;
    unsigned int burst_time;
    unsigned int remaining_burst;
    unsigned int waiting_time;
    unsigned int start_time[ARR_MAX];
    unsigned int end_time[ARR_MAX];
    unsigned short run_count;
} Process;

Process* createProcess(unsigned int pid, unsigned int arrival_time, unsigned int burst_time);
void appendStartTime(Process *p, unsigned int start);
void appendEndTime(Process *p, unsigned int end);

typedef struct {
    Process **processes;
    size_t size;
    double ave_wait_time;
} ProcessList;

ProcessList* createProcessList(size_t num_process);
void freeProcessList(ProcessList *pl);
void printProcessList(ProcessList *pl);