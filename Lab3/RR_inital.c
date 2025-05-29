#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Removed calculate turnaround time function, since it can be done inline



// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    int time = 0;
    int complete = 0;

    for(int i = 0; i < n; i++){
        proc[i].remaining_time = proc[i].burst_time;
    }

    // Make a completion times array to track (only size 100 for now, could expand conditionally if we wanted)
    int orderSize = 100;
    int ordIdx = 0;
    int* executionOrder = (int*)malloc(sizeof(int) * orderSize);
    for(int i = 0; i < orderSize; i++) executionOrder[i] = -1;
    

    while(complete < n){
        for(int i = 0; i < n; i++){
            Process* p = &proc[i];
            // Skip if job done or not yet arrived
            if(p->remaining_time == 0 || p->arrival_time > time) continue;

            // Job not going to finish in this quantum
            if(p->remaining_time > quantum){
                p->remaining_time -= quantum;
                time += quantum;

            }else{
                // Job will finish before end of this quantum.
                time += p->remaining_time;
                p->remaining_time = 0;

                // Calculate turnaround and waiting time
                p->turnaround_time = time - p->arrival_time;
                p->waiting_time = p->turnaround_time - p->burst_time;
                complete++;
            }

            executionOrder[ordIdx++] = p->process_id;
        }
    }
    
    // Print the results
    printf("Execution Order: ");
    for(int i = 0; i < orderSize; i++){
        if(executionOrder[i] == -1){
            printf("\n");
            break;
        }

        printf("P%d ", executionOrder[i]);
    }

    // Free the array.
    free(executionOrder);
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
}

void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 
    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
