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

void calculateTimes(Process proc[], int n, int timeQuantum)
{
    int currentTime = 0;
    int completed = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int ganttChart[1000];
    int ganttSize = 0;
    int queue[1000];
    int front = 0, rear = 0;

    // Enqueue the first process
    queue[rear++] = 0;

    bool isInQueue[n];
    for (int i = 0; i < n; i++)
    {
        isInQueue[i] = false;
    }
    isInQueue[0] = true;

    while (completed != n)
    {
        int idx = queue[front++];
        if (proc[idx].remainingTime > 0)
        {
            if (ganttSize == 0 || ganttChart[ganttSize - 1] != proc[idx].pid)
            {
                ganttChart[ganttSize++] = proc[idx].pid;
            }

            if (proc[idx].remainingTime <= timeQuantum)
            {
                currentTime += proc[idx].remainingTime;
                proc[idx].remainingTime = 0;
                proc[idx].completionTime = currentTime;
                proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
                proc[idx].waitTime = proc[idx].turnaroundTime - proc[idx].burstTime;

                totalWaitTime += proc[idx].waitTime;
                totalTurnaroundTime += proc[idx].turnaroundTime;

                completed++;
            }
            else
            {
                proc[idx].remainingTime -= timeQuantum;
                currentTime += timeQuantum;
            }

            // Enqueue new processes that have arrived by the current time
            for (int i = 1; i < n; i++)
            {
                if (proc[i].arrivalTime <= currentTime && !isInQueue[i] && proc[i].remainingTime > 0)
                {
                    queue[rear++] = i;
                    isInQueue[i] = true;
                }
            }

            // Re-enqueue the current process if it is not yet completed
            if (proc[idx].remainingTime > 0)
            {
                queue[rear++] = idx;
            }
        }
    }

    // Print Gantt Chart
    printf("Gantt Chart:\n|");
    for (int i = 0; i < ganttSize; i++)
    {
        printf(" P%d |", ganttChart[i]);
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
    int n, timeQuantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
    }

    sortProcessesByArrivalTime(proc, n);
    calculateTimes(proc, n, timeQuantum);

    return 0;
}
