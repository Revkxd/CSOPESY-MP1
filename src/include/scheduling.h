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
    int size;
    Process *processes;
    int *arrival;
    int *burst;
} ProcessQueue;

void FCFS(ProcessQueue pq);
void SJF(ProcessQueue pq);
void SRTF(ProcessQueue pq);
void RR(ProcessQueue pq, int quantum);
ProcessQueue createProcessQueue(int num_process);
void printProcessQueue(ProcessQueue pq);
void freeProcessQueue(ProcessQueue pq);
void sortArrival(ProcessQueue pq);
void sortPID(ProcessQueue pq);