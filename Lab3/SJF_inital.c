#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define true 1
#define false 0


typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int bestIdx = -1; 
    int bestTime = INT_MAX;

    // Go through all the processes 
    for(int i = 0; i < n; i++){
        // If the process already done, or comes later ignore for now
        if(proc[i].is_completed || proc[i].arrival_time > current_time) continue;
        
        if(proc[i].remaining_time < bestTime){
            bestIdx = i;
            bestTime = proc[i].remaining_time;
        }
    }

    return bestIdx;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int numComplete = 0;
    int currTime = 0;

    int prev = -1;

    // Initialize the total time this process will take, it is the starting burst time. 
    for(int i = 0; i < n; i++){
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = false;
    }

    // Go until all the process are completed
    while(numComplete < n){
        // Get the next one, skip if none ready yet. 
        int pIdx = findNextProcess(proc, currTime);
        if(pIdx == -1){
            currTime++;
            continue;
        }

        Process* p = &proc[pIdx];  

        if(pIdx != prev){
            printf("Time %d: Process %d starts.\n", currTime, p->process_id);
        }

        // It used a time step. 
        p->remaining_time--;
        currTime++;
        if(p->remaining_time == 0){
            p->is_completed = true;
            p->turnaround_time = currTime - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            printf("Time %d: Process %d completed.\n",currTime, p->process_id);
            numComplete++;
        }

        prev = pIdx;
    }
   
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}
