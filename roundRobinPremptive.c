#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int av;
    int rt;  // Remaining time
};

int compare(const void *a, const void *b) {
    const struct Process *p1 = (const struct Process *)a;
    const struct Process *p2 = (const struct Process *)b;
    return p1->at - p2->at;
}

int main() {
    int n, i, j, time, remaining, flag = 0;
    int time_quantum;
    struct Process processes[10];
    float avg_tat = 0, avg_wt = 0, avg_av = 0;

    printf("Enter Total Process:\t ");
    scanf("%d", &n);
    remaining = n;
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process Number %d :", i + 1);
        scanf("%d", &processes[i].at);
        scanf("%d", &processes[i].bt);
        processes[i].pid = i + 1;
        processes[i].rt = processes[i].bt;
    }

    printf("Enter Time Quantum:\t");
    scanf("%d", &time_quantum);

    qsort(processes, n, sizeof(struct Process), compare);

    for (time = 0, i = 0; remaining != 0;) {
        if (processes[i].at <= time && processes[i].rt > 0) {
            if (processes[i].rt > time_quantum) {
                time += time_quantum;
                processes[i].rt -= time_quantum;
            } else {
                time += processes[i].rt;
                processes[i].rt = 0;
                flag = 1;
            }
            if (flag == 1) {
                processes[i].ct = time;
                processes[i].tat = processes[i].ct - processes[i].at;
                processes[i].wt = processes[i].tat - processes[i].bt;
                processes[i].av = processes[i].at + processes[i].wt;
                avg_tat += processes[i].tat;
                avg_wt += processes[i].wt;
                avg_av += processes[i].av;
                remaining--;
                flag = 0;
            }

            if (i == n - 1) {
                i = 0;
            } else if (processes[i + 1].at <= time) {
                i++;
            } else {
                i = 0;
            }
        } else if (processes[i].at > time) {
            time++;
        } else {
            i++;
            if (i == n) {
                i = 0;
            }
        }
    }

    avg_tat /= n;
    avg_wt /= n;
    avg_av /= n;

    printf("Process\tAT\tBT\tCT\tTAT\tWT\tAV\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt, processes[i].av);
    }

    printf("Average Turnaround Time= %f\n", avg_tat);
    printf("Average Waiting Time= %f\n", avg_wt);
    printf("Average Response Time (Average Time)= %f\n", avg_av);

    return 0;
}

