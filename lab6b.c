#include <stdio.h>
#include <stdlib.h>
// Structure to represent a process
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

// Function to calculate waiting time for each process
void calculateWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    int remaining_burst_time[n];
    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
    }
    int completed = 0;
    int time = 0;
    while (completed < n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && remaining_burst_time[i] > 0 && (shortest == -1 || remaining_burst_time[i] < remaining_burst_time[shortest])) {
                shortest = i;
            }
        }
        if (shortest == -1) {
            time++;
        } else {
            remaining_burst_time[shortest]--;
            if (remaining_burst_time[shortest] == 0) {
                completed++;
                waiting_time[shortest] = time + 1 - processes[shortest].arrival_time - processes[shortest].burst_time;
            }
            time++;
        }
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }
}

// Function to calculate the average waiting time
float calculateAverageWaitingTime(int waiting_time[], int n) {
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
    }
    return total_waiting_time / n;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    // Input process data
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for Process P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }
    int waiting_time[n];
    int turnaround_time[n];
    // Calculate waiting time for SJRF
    calculateWaitingTime(processes, n, waiting_time);
    // Calculate turnaround time for SJRF
    calculateTurnaroundTime(processes, n, waiting_time, turnaround_time);
    // Print waiting and turnaround times for each process
    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].pid, waiting_time[i], turnaround_time[i]);
    }
    // Calculate and print average waiting time for SJRF
    float avg_waiting_time_sjrf = calculateAverageWaitingTime(waiting_time, n);
    printf("Average Waiting Time for SJRF: %.2f\n", avg_waiting_time_sjrf);
    // Reset waiting time array
    for (int i = 0; i < n; i++) {
        waiting_time[i] = 0;
    }
     // Priority (Preemptive) Scheduling Algorithm
    int completed = 0;
    int time = 0;
    while (completed < n) {
        int highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && (highest_priority == -1 || processes[i].priority < processes[highest_priority].priority)) {
                highest_priority = i;
            }
        }
        if (highest_priority == -1) {
            time++;
        } else {
            processes[highest_priority].remaining_time--;
            if (processes[highest_priority].remaining_time == 0) {
                completed++;
                waiting_time[highest_priority] = time + 1 - processes[highest_priority].arrival_time - processes[highest_priority].burst_time;
            }
            time++;
        }
    }
    // Calculate turnaround time for Priority (Preemptive)
    calculateTurnaroundTime(processes, n, waiting_time, turnaround_time);
    // Calculate and print average waiting time for Priority (Preemptive)
    float avg_waiting_time_priority = calculateAverageWaitingTime(waiting_time, n);
    printf("Average Waiting Time for Priority (Preemptive): %.2f\n", avg_waiting_time_priority);
    // Reset waiting time array
    for (int i = 0; i < n; i++) {
        waiting_time[i] = 0;
    }
    // Round Robin Scheduling Algorithm (with time quantum = 2ms)
    int time_quantum = 2;
    int remaining_burst_time[n];
    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
    }
    completed = 0;
    time = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && remaining_burst_time[i] > 0) {
                if (remaining_burst_time[i] <= time_quantum) {
                    time += remaining_burst_time[i];
                    remaining_burst_time[i] = 0;
                    completed++;
                    waiting_time[i] = time - processes[i].arrival_time - processes[i].burst_time;
                } else {
                    time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                }
            }
        }
    }
    // Calculate turnaround time for Round Robin
    calculateTurnaroundTime(processes, n, waiting_time, turnaround_time);
    // Calculate and print average waiting time for Round Robin
    float avg_waiting_time_rr = calculateAverageWaitingTime(waiting_time, n);
    printf("Average Waiting Time for Round Robin: %.2f\n", avg_waiting_time_rr);
    // Compare the algorithms and print the result
    if (avg_waiting_time_sjrf <= avg_waiting_time_priority && avg_waiting_time_sjrf <= avg_waiting_time_rr) {
        printf("SJRF has the lowest average waiting time.\n");
    } else if (avg_waiting_time_priority <= avg_waiting_time_sjrf && avg_waiting_time_priority <= avg_waiting_time_rr) {
        printf("Priority (Preemptive) has the lowest average waiting time.\n");
    } else {
        printf("Round Robin has the lowest average waiting time.\n");
    }
    return 0;
}
