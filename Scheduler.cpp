
#include "Scheduler.h"
#include<iostream>
using namespace std;

Scheduler::Scheduler() {
    
    cout<<"Enter the number of processes ::";
    cin>>this->nop;
    
    burstTime = new int[this->nop];
    wTime = new int[this->nop];
    this->TTT = 0.0;
    this->awt = 0.0;
}

void Scheduler::setProcesses(){

    cout<<"Enter the burst time for::"<<endl;
    for(int i=0;i<nop; i++){
        cout<<"PID "<< i+1<<" ::";
        cin>>burstTime[i];
    }
}

void Scheduler::FCFS(){     
    
    for(int i=0;i<nop; i++){
        if(i == 0)
            wTime[i] = 0;
        else
            wTime[i] = wTime[i-1] + burstTime[i-1];
        
        //Add the accumulative time
        TTT += wTime[i];
    }
    
    cout<<"\n\nArrival time  TAT"<<endl;
    for(int i=0;i<nop;i++){
        cout<<"P"<<i+1<<" ::"<<burstTime[i]<<"   "<<wTime[i]<<endl;
    }
    
    cout<<"\nAverage Wait Time (using FCFS)::"<< TTT/nop<<" mS\n";
    
}

void Scheduler::SJF(){
    //Sort the processes according to burst time
    int temp = 0;
    int process[nop][3]= {0}; //A 2D Array to store process information
    //process[queueNumber][burst time]
    int sorted[nop]; //store the sorted array
    
    //Make a copy of original array
    for(int i=0;i<nop;i++){
        sorted[i] = burstTime[i];
    }
    
    //Sort using bubble sort
    for(int i=0;i<this->nop;i++){
        for(int j=i+1;j<this->nop;j++){
            if(sorted[i]>sorted[j]){// Swap them
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    
    //Get the wait time of each process
    for(int i=0;i<nop;i++){
        if(i==0){
            wTime[i] = 0;
        }else{
            wTime[i] = sorted[i-1] + wTime[i-1];
        }
        //add the wait time
        TTT += wTime[i];
    }
    
    
    //Populate array with new data
    for(int i=0;i<nop;i++){
        for(int j=0;j<3;j++){
            if(j == 0){
                process[i][j] = i+1;
            }else if(j==1){
                process[i][j] = burstTime[i]; 
            }else{
                for(int m=0;m<nop;m++){//Fails if same number appears twice
                    if(sorted[i] == burstTime[m]){
                        process[i][j] = wTime[m+1];
                    }
                }
            }
        }
    }

    
    cout<<"Arrival time  TAT"<<endl;
    for(int i=0;i<nop;i++){
        for(int j=0;j<3;j++){
            cout<<process[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\nAverage Wait Time (using SJF)::"<< TTT/nop<<" mS\n";
    
    cout<<"Order of execution::";
    for(int i=0;i<nop;i++){
        for(int m=0;m<nop;m++){
            if(sorted[i] == burstTime[m]){
                cout<<"P"<<m+1<<" ";
            }
        }
    }
    
}


void Scheduler::SJF_Preemptive(){
    //Sort the processes using the arrival time
    int process[nop][4] = {0};
    
    for(int i=0;i<nop;i++){
        //Set the PID
        process[i][0] = i+1;
        // add the burst time
        process[i][1] = burstTime[i];
        
        // Enter the arrival time
        cout<<"Enter the arrival time for ::\n";
        cout<<"P"<<i+1<<" ::";
        cin>>process[i][2];
         
        //Set the wait time
        process[i][3] = 0;
        
    }
    
    for(int i=0;i<nop;i++){
        
    }
    
    //Display the table
    cout<<"\nBT -Burst time, AT- Arrival Time, WT - Waiting Time"<<endl;
    cout<<"PID\tBT\tAT\tWT"<<endl;
    for(int i=0;i<nop;i++){
        cout<<"P"<<process[i][0]<<"\t"<<process[i][1]<<"\t"<<process[i][2]
                    <<"\t"<<process[i][3]<<endl;
    }
}

void Scheduler::roundRobin(){
    
    int quantum, counter = 0;//Set the time slice
    bool semaphore = true;
    int rTime[20] = {0}; // Store the time remaining;
    int runTime[nop*nop][2] = {0};
    int process[nop][3];
    int flag = 1;
    int i =0;
    int times;
    int turn[nop][2] = {0};
    
    cout<<"Enter the time slice ::";
    cin>>quantum;
    
    
    //Remaining time is equal to burst time
    for(int i=0;i<nop;i++){
        rTime[i] = burstTime[i];
    }

    while(semaphore){
        counter = 0;
        //adjust number of looping
        for(int j =0;j<nop;j++){
            if(rTime[j] != 0){
                times ++;
            }else{
                //store the numbers with zero remaining time
                turn[j][0] = j;
                turn[j][1] = burstTime[j];
            }
        }
        for(int i=0;i<nop;i++){
            if(rTime[i] == 0){
                
            }else if(rTime[i] > 0 && rTime[i] < quantum){
                /**
                 * Set the remaining time to 0
                 */
                rTime[i] = 0;
//                process[i][0]= i;
//                process[i][0]= ;
//                process[i][0]= ;
            }else{
                /**
                 * Remaining time is burst time - quantum
                 */
                rTime[i] = rTime[i] - quantum;
            }
        }
        
        //check if there is a process with a remaining time > 0
        for(int i=0;i<nop;i++){
            cout<<"PID "<<i+1<<" --->"<<rTime[i]<<endl;
            if(rTime[i] > 0){
                counter ++;
            }
        }
        
        if(counter > 0){
            semaphore = true;
        }else{
            semaphore = false;
        }
        
        times = 0;//reset looping times
    }
    
}
