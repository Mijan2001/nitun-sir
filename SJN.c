#include <stdio.h>

#define MAX_PROCESSES 10

struct Process
{
    int pid;      // Process ID
    int arrival;  // Arrival time
    int burst;    // Burst time
    int complete; // Completion time
    int waiting;  // Waiting time
    int turnaround; // Turnaround time
};

// Function prototypes
void sortByBurst(struct Process proc[], int n);
void calculateTimes(struct Process proc[], int n);
void printTable(struct Process proc[], int n);

int main()
{
    struct Process proc[MAX_PROCESSES];
    int i, n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival, &proc[i].burst);
        proc[i].pid = i + 1; // Assign process ID
    }

    sortByBurst(proc, n); // Sort processes by burst time
    calculateTimes(proc, n); // Calculate completion, waiting, and turnaround times
    printTable(proc, n); // Print the results table

    return 0;
}

// Function to sort processes by burst time in ascending order
void sortByBurst(struct Process proc[], int n)
{
    struct Process temp;
    int i, j;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (proc[j].burst > proc[j + 1].burst)
            {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

// Function to calculate completion, waiting, and turnaround times
void calculateTimes(struct Process proc[], int n)
{
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (proc[i].arrival > current_time)
        {
            current_time = proc[i].arrival;
        }
        proc[i].complete = current_time + proc[i].burst;
        proc[i].waiting = proc[i].complete - proc[i].arrival - proc[i].burst;
        proc[i].turnaround = proc[i].complete - proc[i].arrival;
        current_time = proc[i].complete;
    }
}

// Function to print the process table
void printTable(struct Process proc[], int n)
{
    printf("\nProcess\tArrival\tBurst\tComplete\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst, proc[i].complete, proc[i].waiting, proc[i].turnaround);
    }
}



//OUTPUT..................
/*
Enter the number of processes: 3
Enter arrival time and burst time for process 1: 1 7
Enter arrival time and burst time for process 2: 3 3
Enter arrival time and burst time for process 3: 6 2

Process Arrival Burst   Complete        Waiting Turnaround
P3      6       2       8       0       2
P2      3       3       11      5       8
P1      1       7       18      10      17

*/




