#include <stdio.h>

int main() {
    int n, i, j;
    int at[10], bt[10], ct[10], tat[10], wt[10], av[10];
    float avg_tat = 0, avg_wt = 0, avg_av = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
    }

    // Completion time calculation
    ct[0] = at[0] + bt[0];
    for (i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i];
    }

    // Turnaround time calculation
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        avg_tat += tat[i];
    }

    // Waiting time calculation
    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
    }

    // Average Time calculation
    for (i = 0; i < n; i++) {
        av[i] = (at[i] + wt[i]);
        avg_av += av[i];
    }

    avg_tat /= n;
    avg_wt /= n;
    avg_av /= n;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tAV\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], av[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Response Time (Average Time): %.2f\n", avg_av);

    return 0;
}
