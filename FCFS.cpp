#include<bits/stdc++.h>

using namespace std;

struct Process {
    int pid; // Process ID
    int at; // Arrival time
    int bt; // Burst time
    int ct; // Completion time
    int tat; // Turnaround time
    int wt; // Waiting time
};

bool compareArrival(const Process &p1, const Process &p2) {
    return p1.at < p2.at;
}

bool compareBurst(const Process &p1, const Process &p2) {
    return p1.bt < p2.bt;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
        processes[i].pid = i + 1;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    int current_time = processes[0].at;
    int completed = 0;

    while (completed != n) {
        // Find the shortest job among arrived processes
        int min_index = -1;
        int min_bt = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= current_time && processes[i].bt > 0 && processes[i].bt < min_bt) {
                min_index = i;
                min_bt = processes[i].bt;
            }
        }

        if (min_index == -1) {
            // No process arrived yet, advance time
            current_time++;
        } else {
            // Execute the shortest job
            processes[min_index].ct = current_time + processes[min_index].bt;
            processes[min_index].tat = processes[min_index].ct - processes[min_index].at;
            processes[min_index].wt = processes[min_index].tat - processes[min_index].bt;
            completed++;
            current_time = processes[min_index].ct;
        }
    }

    // Calculate average TAT and WT
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += processes[i].tat;
        avg_wt += processes[i].wt;
    }
    avg_tat /= n;
    avg_wt /= n;

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t" << processes[i].at << "\t" << processes[i].bt << "\t"
             << processes[i].ct << "\t" << processes[i].tat << "\t" << processes[i].wt << endl;
    }

    cout << "Average Turnaround Time: " << avg_tat << endl;
    cout << "Average Waiting Time: " << avg_wt << endl;

    return 0;
}
