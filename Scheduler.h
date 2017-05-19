

#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
public:
    Scheduler();
    void setProcesses();
    void FCFS();
    void SJF();
    void SJF_Preemptive();
    void roundRobin();
    
private:
    int *burstTime; //Array containing Burst time
    int *wTime; //Waiting time for each processes
    int nop; //Number of Processes
    double TTT ; //Total time taken
    double awt; //Average Waiting Time
};

#endif /* SCHEDULER_H */

