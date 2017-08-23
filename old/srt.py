#!/usr/bin/env python3

from random import random

pidspace = []
class Job:
    def __init__(self, PID):
        self.pid = PID
        print("Enter arrival time, burst time for pid {}:".format(self.pid))
        self.arrivalTime = int(input())
        self.burstTime = int(input())
        self.waitingTime = 0
        self.completionTime = 0
        self.turnaroundTime = 0
    def lesserThan(self, other):
        if self.arrivalTime == other.arrivalTime:
            if self.burstTime == other.burstTime:
                if self.pid < other.pid:
                    return True
            if self.burstTime < other.burstTime:
                return True
        if self.arrivalTime < other.arrivalTime:
            return True
        return False
    def calcValue(self, prev=None):
        if prev is None or self.arrivalTime > prev.completionTime:
            self.completionTime = self.burstTime + self.arrivalTime
        else:
            self.completionTime = self.burstTime + prev.completionTime

        self.turnaroundTime = self.completionTime - self.arrivalTime
        self.waitingTime = self.turnaroundTime - self.burstTime

<<<<<<< HEAD
JOBS = []
JOBQUEUE = []
=======
CLOCK = 0
JOBS = []
JOBQUEUE = []
WAITQUEUE = []
>>>>>>> 73ae78d1e8f2792b8700c342ed981b46bb52ddbe

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
prevJob = None

for job in JOBQUEUE:
    job.calcValue(prevJob)
<<<<<<< HEAD
=======
    CLOCK += job.burstTime
    nextJob = None
    for possibleNextJob in JOBQUEUE:
        if possibleNextJob.arrivalTime < CLOCK:
            WAITQUEUE.append(possibleNextJob)

>>>>>>> 73ae78d1e8f2792b8700c342ed981b46bb52ddbe
    totalWaitingTime += job.waitingTime
    totalTurnaroundTime += job.turnaroundTime
    print("{}\t{}\t{}\t\t{}\t\t{}\t\t{}".format(job.pid, job.burstTime, job.arrivalTime,
                                                job.waitingTime, job.completionTime, job.turnaroundTime))
    prevJob = job
print('''\nAll jobs completed in {}
Average waiting time: {}
Average turnaround time: {}
'''.format(float(prevJob.completionTime), totalWaitingTime/n, totalTurnaroundTime/n))
