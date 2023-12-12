#pragma once

#define ARR_MAX 128

#include <inttypes.h>

typedef struct {
    uint64_t pid;
    uint64_t arrival_time;
    uint64_t burst_time;
    uint64_t remaining_burst;
    uint64_t waiting_time;
    uint64_t start_time[ARR_MAX];
    uint64_t end_time[ARR_MAX];
    size_t run_count;
} Process;

Process* createProcess(uint64_t pid, uint64_t arrival_time, uint64_t burst_time);
void appendStartTime(Process *p, uint64_t start);
void appendEndTime(Process *p, uint64_t end);

typedef struct {
    Process **processes;
    size_t size;
    double ave_wait_time;
} ProcessList;

ProcessList* createProcessList(size_t num_process);
void freeProcessList(ProcessList *pl);
void printProcessList(ProcessList *pl);