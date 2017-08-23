#!/usr/bin/env python3

from random import random
import subprocess
import os

pidspace = []
class Job:
    def __init__(self, PID):
        self.pid = PID
        print("Enter arrival time, burst time for pid {}:".format(self.pid))
        self.burstTime = int(subprocess.check_output('wc -w {} | cut -f1 -d'"'"' '"'"''.format(PID), shell=True))
        self.arrivalTime = int(os.stat(PID).st_mtime)
        self.waitingTime = 0
        self.completionTime = 0
        self.turnaroundTime = 0
    def __str__(self, ):
        return "{}  {}  {}  {}  {}  {}"\
           .format(self.pid, self.arrivalTime, self.burstTime, self.completionTime, self.waitingTime, self.turnaroundTime)
    def lesserThan(self, other):
        if self.arrivalTime == other.arrivalTime:
            if self.pid < other.pid:
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

JOBS = []
JOBQUEUE = []

# Get list of files in current directory and generate that many process ids

FILES = []
# ignore the script itself
for f in os.listdir():
    if not f.endswith(".py") and not f.endswith(".out") and not f.endswith("makefile"):
        FILES.append(f)
        print(f)
n = len(FILES)
print("Number of files in directory = {}".format(n))

# Populate the PID with n unique random numbers
# while pidspace.__len__() < n:
#     newPid = int(random() * 10000)
#     if pidspace.__contains__(newPid):
#         continue
#     else:
#         pidspace.append(newPid)

for file in FILES:
    a = Job(file)
    JOBS.append(a)

minArrival = min([job.arrivalTime for job in JOBS]) - 10

for job in JOBS:
    job.arrivalTime -= minArrival

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
    totalWaitingTime += job.waitingTime
    totalTurnaroundTime += job.turnaroundTime
    # print(job)
    print("{}\t{}\t{}\t\t{}\t\t{}\t\t{}".format(job.pid, job.burstTime, job.arrivalTime,
                                                job.waitingTime, job.completionTime, job.turnaroundTime))
    prevJob = job
print('''All jobs completed in {}
      Average waiting time: {}
      Average turnaround time: {}
      '''.format(prevJob.completionTime, totalWaitingTime/n, totalTurnaroundTime/n))
