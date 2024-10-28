#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int pid; // Process ID
    int arrivalTime;
    int burstTime;
    int waitTime;
    int turnaroundTime;
    int completionTime;
} Process;

void sortProcessesByArrivalTime(Process proc[], int n)
{
    Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (proc[i].arrivalTime > proc[j].arrivalTime)
            {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

int findNextProcess(Process proc[], int n, int currentTime, bool isCompleted[])
{
    int minBurstTime = __INT_MAX__;
    int minIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!isCompleted[i] && proc[i].arrivalTime <= currentTime && proc[i].burstTime < minBurstTime)
        {
            minBurstTime = proc[i].burstTime;
            minIndex = i;
        }
    }

    return minIndex;
}

void calculateCompletionTime(Process proc[], int n, int ganttChart[], int *ganttSize)
{
    int time = 0;
    int completed = 0;
    bool isCompleted[n];

    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = false;
    }

    while (completed != n)
    {
        int minIndex = findNextProcess(proc, n, time, isCompleted);

        if (minIndex != -1)
        {
            ganttChart[*ganttSize] = proc[minIndex].pid;
            (*ganttSize)++;
            time += proc[minIndex].burstTime;
            proc[minIndex].completionTime = time;
            proc[minIndex].turnaroundTime = proc[minIndex].completionTime - proc[minIndex].arrivalTime;
            proc[minIndex].waitTime = proc[minIndex].turnaroundTime - proc[minIndex].burstTime;
            isCompleted[minIndex] = true;
            completed++;
        }
        else
        {
            time++;
        }
    }
}

void printProcesses(Process proc[], int n)
{
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].completionTime, proc[i].waitTime, proc[i].turnaroundTime);
    }
}

void calculateAndPrintAverages(Process proc[], int n)
{
    float totalWaitTime = 0;
    float totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++)
    {
        totalWaitTime += proc[i].waitTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }

    printf("Average Wait Time: %.2f\n", totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

void printGanttChart(int ganttChart[], int ganttSize)
{
    printf("Gantt Chart:\n|");
    for (int i = 0; i < ganttSize; i++)
    {
        printf(" P%d |", ganttChart[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    int ganttChart[n];
    int ganttSize = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    sortProcessesByArrivalTime(proc, n);
    calculateCompletionTime(proc, n, ganttChart, &ganttSize);
    printProcesses(proc, n);
    calculateAndPrintAverages(proc, n);
    printGanttChart(ganttChart, ganttSize);

    return 0;
}
