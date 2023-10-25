from copy import deepcopy

class Process:
    def __init__(self, pid, arrival, burst) -> None:
        self.process_id = pid
        self.arrival_time = arrival
        self.burst_time = burst
        self.completion_time = 0
        self.waiting_time = 0

def SJF(processes):
    sorted_processes = sorted(processes, key=lambda x: x.burst_time)
    result = []
    current_time = 0
    process_queue = []
    while len(sorted_processes) > 0 or len(process_queue) > 0:
        for process in sorted_processes:
            if process.arrival_time <= current_time:
                process_queue.append(process)
                sorted_processes.remove(process)

        if len(process_queue) == 0:
            current_time += 1
            continue
        
        process_queue.sort(key=lambda x: x.burst_time)
        process = process_queue.pop(0)
        process.completion_time = current_time + process.burst_time
        process.waiting_time = current_time - process.arrival_time
        current_time += process.burst_time
        result.append(process)

    result.sort(key=lambda x: x.process_id)
    return result

def average_waiting_time(processes):
    total_waiting_time = 0
    for process in processes:
        total_waiting_time += process.waiting_time
        print(f'Process {process.process_id}: {process.waiting_time}')
    print(total_waiting_time / len(processes))

if __name__ == '__main__':
    algo, num_process, quantum = 0, 0, 0
    processes = []
    with open('test/testcase1.txt', 'r') as f:
        algo, num_process, quantum = [int(x) for x in f.readline().split()]
        for _ in range(num_process):
            pid, arrival, burst = [int(x) for x in f.readline().split()]
            process = Process(pid, arrival, burst)
            processes.append(process)

    average_waiting_time(SJF(deepcopy(processes)))