#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int av;
};

int compare(const void *a, const void *b) {
    const struct Process *p1 = (const struct Process *)a;
    const struct Process *p2 = (const struct Process *)b;

    if (p1->at != p2->at) {
        return p1->at - p2->at;
    }
    return p1->bt - p2->bt;
}

int main() {
    int n, i, j;
    struct Process processes[10];
    float avg_tat = 0, avg_wt = 0, avg_av = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &processes[i].at);
        printf("Burst time: ");
        scanf("%d", &processes[i].bt);
        processes[i].pid = i + 1; // assign process ID
    }

    // Sort processes based on arrival time and burst time
    qsort(processes, n, sizeof(struct Process), compare);

    // Completion time, turnaround time, waiting time, and average time calculation
    int current_time = processes[0].at;
    for (i = 0; i < n; i++) {
        processes[i].ct = current_time + processes[i].bt;
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        processes[i].av = processes[i].at + processes[i].wt;

        current_time = processes[i].ct;

        avg_tat += processes[i].tat;
        avg_wt += processes[i].wt;
        avg_av += processes[i].av;
    }

    avg_tat /= n;
    avg_wt /= n;
    avg_av /= n;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tAV\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at,
               processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt, processes[i].av);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Response Time (Average Time): %.2f\n", avg_av);

    return 0;
}

