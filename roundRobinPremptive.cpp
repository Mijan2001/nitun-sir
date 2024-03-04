
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int av;
    int rt; // Remaining time
};

bool compare(const Process &p1, const Process &p2) {
    return p1.at < p2.at;
}

int main() {
    int n, i, time, remaining, flag = 0;
    int time_quantum;
    vector<Process> processes(10);
    float avg_tat = 0, avg_wt = 0, avg_av = 0;

    cout << "Enter Total Process:\t ";
    cin >> n;
    remaining = n;

    // Input arrival time and burst time for each process
    for (i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process Number " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
        processes[i].pid = i + 1;
        processes[i].rt = processes[i].bt;
    }

    cout << "Enter Time Quantum:\t";
    cin >> time_quantum;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compare);

    for (time = 0, i = 0; remaining != 0;) {
        if (processes[i].at <= time && processes[i].rt > 0) {
            // Execute process based on time quantum
            if (processes[i].rt > time_quantum) {
                time += time_quantum;
                processes[i].rt -= time_quantum;
            } else {
                time += processes[i].rt;
                processes[i].rt = 0;
                flag = 1;
            }

            if (flag == 1) {
                // Calculate completion time, TAT, WT, and AV
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

            // Move to next process based on arrival time
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

    cout << "Process\tAT\tBT\tCT\tTAT\tWT\tAV\n";
    for (i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t" << processes[i].at << "\t"
             << processes[i].bt << "\t" << processes[i].ct << "\t"
             << processes[i].tat << "\t" << processes[i].wt << "\t"
             << processes[i].av << endl;
    }

    cout << "Average Turnaround Time= " << avg_tat << endl;
    cout << "Average Waiting Time= " << avg_wt << endl;
    cout << "Average Response Time (Average Time)= " << avg_av << endl;

    return 0;
}
