#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitTime;
    int completionTime;
    int turnAroundTime;
};

void sortProcessesByArrivalTime(vector<Process> &proc, int n)
{
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b)
         { return a.arrivalTime < b.arrivalTime; });
}

bool compareByArrivalTime(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    vector<Process> proc(n);
    cout << "Enter arrival time and burst time for the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " : ";
        cin >> proc[i].arrivalTime >> proc[i].burstTime;
        proc[i].pid = i + 1;
    }

    // sortProcessesByArrivalTime(proc, n);
    sort(proc.begin(), proc.end(), compareByArrivalTime);
    // calculateTimes(proc, n);

    printf("\nGantt Chart: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d | ", proc[i].pid);
    }
    printf("\n\n");
    return 0;
}