#include <stdio.h>

struct Process
{
    int pid;         // Process ID
    int at;          // Arrival Time
    int bt;          // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int av;         // Average Time (AT + WT)
    int prio;       // Priority (lower number is higher priority)
};

int compare(const void *a, const void *b)
{
    const struct Process *p1 = (const struct Process *)a;
    const struct Process *p2 = (const struct Process *)b;

    // Prioritize by arrival time in case of equal priority
    if (p1->prio == p2->prio)
    {
        return p1->at - p2->at;
    }
    return p1->prio - p2->prio;  // Sort by ascending priority (lower number first)
}

int main()
{
    int n, time, remaining = 0;
    struct Process processes[10];
    float avg_tat = 0, avg_wt = 0, avg_av = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time, burst time, and priority (lower number is higher) for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].at);
        printf("Burst Time: ");
        scanf("%d", &processes[i].bt);
        printf("Priority: ");
        scanf("%d", &processes[i].prio);
        processes[i].pid = i + 1;       // Assign process ID
        remaining++; // Add to remaining count
    }

    qsort(processes, n, sizeof(struct Process), compare); // Sort by priority and arrival time

    time = processes[0].at; // Start from the first process's arrival time

    for (int i = 0; remaining > 0; i = (i + 1) % n)   // Iterate round-robin
    {
        // Process with current lowest priority (lowest numerical value) and has arrived
        if (processes[i].at <= time && processes[i].bt > 0)
        {
            processes[i].bt--; // Execute one unit of burst time
            if (processes[i].bt == 0)   // Process completed
            {
                processes[i].ct = time + 1;
                processes[i].tat = processes[i].ct - processes[i].at;
                processes[i].wt = processes[i].tat - processes[i].bt;
                processes[i].av = processes[i].at + processes[i].wt;
                avg_tat += processes[i].tat;
                avg_wt += processes[i].wt;
                avg_av += processes[i].av;
                remaining--;
            }
            time++; // Advance time by 1 unit after each process is executed
        }
        else
        {
            // Skip processes that haven't arrived or are finished
            time = processes[i].at; // Move to next process's arrival time (if earlier)
        }
    }

    avg_tat /= n;
    avg_wt /= n;
    avg_av /= n;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tAV\tPRIO\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at,
               processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt, processes[i].av, processes[i].prio);
    }

    printf("Average Turnaround Time= %.2f\n", avg_tat);
    printf("Average Waiting Time= %.2f\n", avg_wt);
    printf("Average Response Time (Average Time)= %.2f\n", avg_av);

    return 0;
}
