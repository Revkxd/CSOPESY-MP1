#pragma once

#include "process.h"
#include "queue.h"

void sortArrival(Process **pl, int size);
void sortBurst(Process **pl, int size);
void sortPID(Process **pl, int size);
void sortQueueArrival(ProcessQueue* pq);
void sortQueueBurst(ProcessQueue* pq);