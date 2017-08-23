#!/usr/bin/env python3

import tabulate
from job import Job
import sys


sys.stdin = open('hrrnin', 'r')

pidspace = []

JOBS = []

print("Number of jobs:")
n = int(input())

pidspace = list(range(n))

for pid in pidspace:
    a = Job(pid)
    a.input()
    JOBS.append(a)

curJobIndex = -1
CLOCK = -1

def chooseJob():
    global curJobIndex, JOBS, CLOCK

    for i, job in enumerate(JOBS):
        JOBS[i].calcrr()
    # maxrr = max([job.rr if not job.complete else -1 for job in JOBS])
    # for i, job in enumerate(JOBS):
    #     if job.rr == maxrr:
    #         curJobIndex = i

    for i, job in enumerate(JOBS):
        if job.complete:
            continue
        if job.arrivalTime <= CLOCK:
            JOBS[i].waiting = True
            if curJobIndex == -1:
                curJobIndex = i
                JOBS[i].waiting = False
                continue
            if job.rr < JOBS[curJobIndex].rr:
                continue
            else:
                if job.rr == JOBS[curJobIndex].rr:
                    if job.arrivalTime > JOBS[curJobIndex].arrivalTime:
                        continue
                JOBS[curJobIndex].waiting = True
                JOBS[i].waiting = False
                curJobIndex = i
    return curJobIndex

while pidspace:
    CLOCK += 1
    if curJobIndex == -1:
        curJobIndex = chooseJob()
    if curJobIndex != -1:
        print("|", curJobIndex, "|", end='', sep='')
        JOBS[curJobIndex].remainingTime -= 1
    else:
        print("|", "|", end='')
    for i, job in enumerate(JOBS):
        if job.complete:
            continue
        if job.waiting:
            JOBS[i].waitingTime += 1
        if job.remainingTime == 0:
            if i == curJobIndex:
                curJobIndex = -1
            JOBS[i].complete = True
            JOBS[i].completionTime = CLOCK+1
            pidspace.remove(i)

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
