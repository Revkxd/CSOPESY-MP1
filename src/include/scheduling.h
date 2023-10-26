#pragma once

#include "process.h"

void FCFS(ProcessList *pl);
void SJF(ProcessList *pl);
void SRTF(ProcessList *pl);
void RR(ProcessList *pl, int quantum);