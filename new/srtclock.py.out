#!/usr/bin/env python3

from random import random
from job import Job

pidspace = []

CLOCK = 0
JOBS = []
JOBQUEUE = []
WAITQUEUE = []

print("Number of jobs:")
n = int(input())

# Populate the PID with n unique random numbers
while len(pidspace) < n:
    newPid = int(random() * 10000)
    if pidspace.__contains__(newPid):
        continue
    else:
        pidspace.append(newPid)

for pid in pidspace:
    a = Job(pid)
    JOBS.append(a)

for i in range(len(JOBS)):
    firstJob = JOBS[i]
    for j in range(i+1, len(JOBS)):
        if JOBS[j].lesserThan(firstJob):
            firstJob = JOBS[j]
    firstJobIndex = JOBS.index(firstJob)
    JOBS[firstJobIndex] = JOBS[i]
    JOBQUEUE.append(firstJob)

totalWaitingTime = 0
totalTurnaroundTime = 0

print("\n\nPID\tBurstT\tArrivalT\tWaitingT\tCompletionT\tTurnaroundT")

curJob = JOBQUEUE[0]
for job in JOBQUEUE:
    CLOCK += 1
    nextJob = None

    totalWaitingTime += job.waitingTime
    totalTurnaroundTime += job.turnaroundTime
    print("{}\t{}\t{}\t\t{}\t\t{}\t\t{}".format(job.pid, job.burstTime, job.arrivalTime,
                                                job.waitingTime, job.completionTime, job.turnaroundTime))
    prevJob = job
print('''\nAll jobs completed in {}
Average waiting time: {}
Average turnaround time: {}
'''.format(float(prevJob.completionTime), totalWaitingTime/n, totalTurnaroundTime/n))
