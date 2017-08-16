#!/usr/bin/env python3

class Job:
    def __init__(self, PID):
        self.pid = PID
        print("Enter arrival time, burst time for pid {}:".format(self.pid))
        self.arrivalTime = int(input())
        self.burstTime = int(input())
        self.waitingTime = 0
        self.completionTime = 0
        self.turnaroundTime = 0
