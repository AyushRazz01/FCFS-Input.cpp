#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id;             // process id
    int arrival_time;    // arrival time
    int burst_time;      // burst time
    int completion_time; // completion time
    int turnaround_time; // turnaround time
    int waiting_time;    // waiting time
    int start_time;      //start time
};

void findCompletionTime(Process proc[], int n) {
    proc[0].start_time = max(0, proc[0].arrival_time); // First process starts at its arrival time or time 0
    proc[0].completion_time = proc[0].start_time + proc[0].burst_time;
    for (int i = 1; i < n; i++) {
        // Handle idle time: if the next process arrives after the last one finishes
        if (proc[i].arrival_time > proc[i - 1].completion_time) {
            proc[i].start_time = proc[i].arrival_time; // Start when it arrives (idle time in system)
        } else {
            proc[i].start_time = proc[i - 1].completion_time; // Continue from last process's completion
        }
        proc[i].completion_time = proc[i].start_time + proc[i].burst_time;
    }
}

void findTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void findWaitingTime(Process proc[], int n) {
    proc[0].waiting_time = 0;

    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        if (proc[i].waiting_time < 0) {

            proc[i].waiting_time = 0;
        }
    }
}

void findFCFS(Process proc[], int n) {
    findCompletionTime(proc, n);
    findTurnaroundTime(proc, n);
    findWaitingTime(proc, n);
}

double findAvgTurnaroundTime(Process proc[], int n) {
    int total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_tat += proc[i].turnaround_time;
    }
    return (double)total_tat / n;
}

double findAvgWaitingTime(Process proc[], int n) {
    int total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
    }
    return (double)total_wt / n;
}

void printTable(Process proc[], int n) {
    cout << "------------------------------------------------------------------------------------------\n";
    cout << "| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n";
    cout << "------------------------------------------------------------------------------------------\n";


    for (int i = 0; i < n; i++) {
        cout << "|    " << proc[i].id << "    |      "
             << proc[i].arrival_time << "      |     "
             << proc[i].burst_time << "        |      "
             << proc[i].completion_time << "      |    "
             << proc[i].turnaround_time << "        |      "
             << proc[i].waiting_time << "     |\n";
    }

    cout << "-----------------------------------------------------------------------------------------\n";

    // Print average turnaround time and waiting time
    cout << "\nAverage Turnaround Time: " << findAvgTurnaroundTime(proc, n) << endl;
    cout << "Average Waiting Time: " << findAvgWaitingTime(proc, n) << endl;
}


void printGanttChart(Process proc[], int n) {
    cout << "\nGantt Chart:\n";
    
    // Print the top border
    for (int i = 0; i < n; i++) {
        cout << "---------";}
    cout << "\n";

    // Print the process IDs in the chart
    for (int i = 0; i < n; i++) {
        cout << "|   P" << proc[i].id << "   ";}
    cout << "|\n";

    // Print the bottom border
    for (int i = 0; i < n; i++) {
        cout << "---------";}
    cout << "\n";

    // Print the time markers
    cout << proc[0].start_time; // The start time of the first process
    for (int i = 0; i < n; i++) {
        cout << "       " << proc[i].completion_time; // Print the completion time of each process
        }
    cout << "\n";}


int main() {
    int n;
    cout << "Enter The Number of Processes: ";
    cin >> n;

    Process proc[n]; // Variable length array (VLA), though consider using std::vector for dynamic sizing
    cout << "Enter Process Details (ID, Arrival, Burst):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Enter Process " << i + 1 << ":\n";
        cout << "ID: ";
        cin >> proc[i].id;
        cout << "Arrival Time: ";
        cin >> proc[i].arrival_time;
        cout << "Burst Time: ";
        cin >> proc[i].burst_time;
    }

    findFCFS(proc, n);
    printGanttChart(proc, n);
    printTable(proc, n); // Pass the correct array here

    return 0;
}
