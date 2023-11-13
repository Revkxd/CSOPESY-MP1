#pragma once

#define ARR_MAX 64

typedef struct {
    size_t pid;
    size_t arrival_time;
    size_t burst_time;
    size_t remaining_burst;
    size_t waiting_time;
    size_t start_time[ARR_MAX];
    size_t end_time[ARR_MAX];
    size_t run_count;
} Process;

Process* createProcess(size_t pid, size_t arrival_time, size_t burst_time);
void appendStartTime(Process *p, size_t start);
void appendEndTime(Process *p, size_t end);

typedef struct {
    Process **processes;
    size_t size;
    double ave_wait_time;
} ProcessList;

ProcessList* createProcessList(size_t num_process);
void freeProcessList(ProcessList *pl);
void printProcessList(ProcessList *pl);