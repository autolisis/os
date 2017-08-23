#!/usr/bin/env python3

class Job:
    def __init__(self, PID = None):
        if PID is None:
            self.pid = -1
        else:
            self.pid = PID
        self.arrivalTime = 0
        self.burstTime = 0
        self.waitingTime = 0
        self.remainingTime = 0
        self.completionTime = 0
        self.turnaroundTime = 0
        self.complete = False
        self.waiting = False
        self.rr = 0.0
    def __str__(self, ):
        return "{}  {}  {}  {}  {}  {}"\
           .format(self.pid, self.arrivalTime, self.burstTime, self.completionTime, self.waitingTime, self.turnaroundTime)
    def input(self):
        print("Enter arrival time, burst time for pid {}:".format(self.pid))
        self.arrivalTime = int(input())
        self.burstTime = int(input())
        self.remainingTime = self.burstTime
    def calc(self, ):
        self.turnaroundTime = self.completionTime - self.arrivalTime
        self.waitingTime = self.turnaroundTime - self.burstTime
    def calcrr(self, ):
        self.rr = 1 + float(self.waitingTime / self.burstTime)
