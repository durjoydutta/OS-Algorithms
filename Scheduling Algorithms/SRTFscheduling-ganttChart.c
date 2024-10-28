#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int pid; // Process ID
    int arrivalTime;
    int burstTime;
    int remainingTime;
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

int findNextProcess(Process proc[], int n, int currentTime)
{
    int minRemainingTime = __INT_MAX__;
    int minIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && proc[i].remainingTime < minRemainingTime)
        {
            minRemainingTime = proc[i].remainingTime;
            minIndex = i;
        }
    }

    return minIndex;
}

void calculateTimes(Process proc[], int n)
{
    int currentTime = 0;
    int completed = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int ganttChart[1000];
    int ganttSize = 0;
    bool isStarted = false;

    while (completed != n)
    {
        int minIndex = findNextProcess(proc, n, currentTime);

        if (minIndex != -1)
        {
            if (!isStarted || ganttChart[ganttSize - 1] != proc[minIndex].pid)
            {
                ganttChart[ganttSize++] = proc[minIndex].pid;
            }
            isStarted = true;

            proc[minIndex].remainingTime--;
            currentTime++;

            if (proc[minIndex].remainingTime == 0)
            {
                proc[minIndex].completionTime = currentTime;
                proc[minIndex].turnaroundTime = proc[minIndex].completionTime - proc[minIndex].arrivalTime;
                proc[minIndex].waitTime = proc[minIndex].turnaroundTime - proc[minIndex].burstTime;

                totalWaitTime += proc[minIndex].waitTime;
                totalTurnaroundTime += proc[minIndex].turnaroundTime;

                completed++;
            }
        }
        else
        {
            ganttChart[ganttSize++] = -1; // Idle time
            currentTime++;
        }
    }

    // Print Gantt Chart
    printf("Gantt Chart:\n|");
    for (int i = 0; i < ganttSize; i++)
    {
        if (ganttChart[i] == -1)
        {
            printf(" Idle |");
        }
        else
        {
            printf(" P%d |", ganttChart[i]);
        }
    }
    printf("\n");

    // Print Process Details
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].completionTime, proc[i].waitTime, proc[i].turnaroundTime);
    }

    // Print Average Times
    printf("Average Wait Time: %.2f\n", (float)totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
    }

    sortProcessesByArrivalTime(proc, n);
    calculateTimes(proc, n);

    return 0;
}
