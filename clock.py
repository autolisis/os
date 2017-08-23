#!/usr/bin/env python3

from random import random
from job import Job
import sys


sys.stdin = open('in', 'r')

pidspace = []

JOBS = []
# WAITING = []
# INCOMPLETE = []
# COMPLETE = []

print("Number of jobs:")
n = int(input())

# Populate the PID with n unique random numbers
pidspace = list(range(n))
# while len(pidspace) < n:
#     newPid = int(random() * 10000)
#     if pidspace.__contains__(newPid):
#         continue
#     else:
#         pidspace.append(newPid)

for pid in pidspace:
    a = Job(pid)
    a.input()
    JOBS.append(a)

curJobIndex = -1
T = True
F = False

CLOCK = -1
while pidspace:
    CLOCK += 1
    for i, job in enumerate(JOBS):
        if job.complete:
            continue
        if job.arrivalTime <= CLOCK:
            JOBS[i].waiting = T
            if curJobIndex == -1:
                curJobIndex = i
                JOBS[i].waiting = F
                continue
            if job.remainingTime <= JOBS[curJobIndex].remainingTime:
                if job.remainingTime == JOBS[curJobIndex].remainingTime:
                    if job.arrivalTime > JOBS[curJobIndex].arrivalTime:
                        continue
                JOBS[curJobIndex].waiting = T
                JOBS[i].waiting = F
                curJobIndex = i
    if curJobIndex != -1:
        JOBS[curJobIndex].remainingTime -= 1
    for i, job in enumerate(JOBS):
        if job.complete:
            continue
        if job.waiting:
            JOBS[i].waitingTime += 1
        if job.remainingTime == 0:
            if i == curJobIndex:
                curJobIndex = -1
            JOBS[i].complete = T
            JOBS[i].completionTime = CLOCK
            pidspace.remove(i)

for job in JOBS:
    print(job)
# totalWaitingTime = 0
# totalTurnaroundTime = 0

# print("\n\nPID\tBurstT\tArrivalT\tWaitingT\tCompletionT\tTurnaroundT")

# for job in JOBS:
#     CLOCK += 1
#     nextJob = None

#     totalWaitingTime += job.waitingTime
#     totalTurnaroundTime += job.turnaroundTime
#     print("{}\t{}\t{}\t\t{}\t\t{}\t\t{}".format(job.pid, job.burstTime, job.arrivalTime,
#                                                 job.waitingTime, job.completionTime, job.turnaroundTime))
#     prevJob = job
# print('''\nAll jobs completed in {}
# Average waiting time: {}
# Average turnaround time: {}
# '''.format(float(prevJob.completionTime), totalWaitingTime/n, totalTurnaroundTime/n))
