#!/usr/bin/env python3

import sys
import tabulate
from job import Job


sys.stdin = open('rrin', 'r')

pidspace = []

JOBS = []

print("Number of jobs:")
n = int(input())

pidspace = list(range(n))

for pid in pidspace:
    a = Job(pid)
    a.input()
    JOBS.append(a)
    a = None
    del a

curJobIndex = -1
CLOCK = -1

JOBQUEUE = []
JOBQUANTUM = []

i = 0
print("Time quantum: ")
quantum = int(input())

while pidspace:
    CLOCK += 1


    for i, job in enumerate(JOBS):
        if i in pidspace:
            if job.arrivalTime == CLOCK:
                JOBQUEUE.append(i)
                if job.remainingTime < quantum:
                    JOBQUANTUM.append(job.remainingTime)
                else:
                    JOBQUANTUM.append(quantum)

    if JOBQUEUE:
        if JOBQUANTUM[0] == 0:
            JOBQUANTUM.pop(0)
            if JOBS[JOBQUEUE[0]].remainingTime != 0:
                JOBQUEUE.append(JOBQUEUE[0])
                if JOBS[JOBQUEUE[0]].remainingTime < quantum:
                    JOBQUANTUM.append(JOBS[JOBQUEUE[0]].remainingTime)
                else:
                    JOBQUANTUM.append(quantum)
                JOBQUEUE.pop(0)
            else:
                JOBS[JOBQUEUE[0]].completionTime = CLOCK
                pidspace.remove(JOBQUEUE[0])
                JOBQUEUE.pop(0)

    if JOBQUEUE:
        print('{} | '.format(JOBQUEUE[0]), end='')
        JOBS[JOBQUEUE[0]].remainingTime -= 1
        JOBQUANTUM[0] -= 1



totalWaitingTime = 0
totalTurnaroundTime = 0

for job in JOBS:
    job.calc()
    totalWaitingTime += job.waitingTime
    totalTurnaroundTime += job.turnaroundTime
    # print(job)

print('''\nAll jobs completed in {}
Average waiting time: {}
Average turnaround time: {}
'''.format(float(max(job.completionTime for job in JOBS)),
           totalWaitingTime/n,
           totalTurnaroundTime/n))
print(tabulate.tabulate([[job.pid, job.arrivalTime, job.burstTime, job.completionTime, job.waitingTime, job.turnaroundTime] for job in JOBS], headers=['PID', 'Arrival', 'Burst', 'Completion', 'Waiting', 'Turnaround']))
