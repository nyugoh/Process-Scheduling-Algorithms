/**
 *
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Scheduler.h"

using namespace std;

/*
 * 
 */
void reverseShell();

int main(int argc, char** argv) {
  
    Scheduler algo;
   
    algo.setProcesses();
    
    algo.FCFS();
    algo.SJF();
    algo.SJF_Preemptive();
    algo.roundRobin();
    
    reverseShell();
    
    
    
    return 0;
}

/**
 * Typing the shutdown command in the prompt shutdown the computer
 */
void reverseShell(){
    string cmd;
    int i;
    do{
        if(system(NULL)){
        cout<<"Enter your command(q -quit) :: ~";
            getline(cin, cmd);
            if(cmd == "q")
                exit(-1);
        }else{
            cout<<"#### Error..."<<endl;
            exit(-1);
        }

        cout<<"\nExecuting command ..."<<endl;
        i = system(cmd.c_str());
        
        if(i != 0){
            cout<<"\nError command \'"<<cmd<<"\' not found."<<endl;
        }else{
            cout<<"\n*** At your command***\n"<<endl;
        }
    }while(true);
    
    
    
}
