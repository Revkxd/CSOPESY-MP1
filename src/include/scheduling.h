#pragma once

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
} Process;

void FCFS(Process processes[]);
void SJF(Process processes[]);
void SRTF(Process processes[]);
void RR(Process processes[], int quantum);