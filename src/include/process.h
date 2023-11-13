#pragma once

#define ARR_MAX 64

#include <inttypes.h>

typedef struct {
    uint32_t pid;
    uint32_t arrival_time;
    uint32_t burst_time;
    uint32_t remaining_burst;
    uint32_t waiting_time;
    uint32_t start_time[ARR_MAX];
    uint32_t end_time[ARR_MAX];
    size_t run_count;
} Process;

Process* createProcess(uint32_t pid, uint32_t arrival_time, uint32_t burst_time);
void appendStartTime(Process *p, uint32_t start);
void appendEndTime(Process *p, uint32_t end);

typedef struct {
    Process **processes;
    size_t size;
    double ave_wait_time;
} ProcessList;

ProcessList* createProcessList(size_t num_process);
void freeProcessList(ProcessList *pl);
void printProcessList(ProcessList *pl);