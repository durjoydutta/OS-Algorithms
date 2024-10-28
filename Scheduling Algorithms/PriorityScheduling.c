#include <stdio.h>

// Priority scheduling non-preemptive
typedef struct process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitTime;
    int completionTime;
    int turnAroundTime;
    int priority;    // higher value means higher priority
    int isCompleted; // flag to check if the process is completed
} Process;

void sortProcessesByArrival(Process proc[], int n)
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
    int highestPriorityIndex = -1;
    for (int i = 0; i < n; i++)
    {
        if (proc[i].arrivalTime <= currentTime && !proc[i].isCompleted)
        {
            if (highestPriorityIndex == -1 || proc[i].priority > proc[highestPriorityIndex].priority)
            {
                highestPriorityIndex = i;
            }
        }
    }
    return highestPriorityIndex;
}

void calculateTimes(Process proc[], int n)
{
    int currentTime = 0;
    int totalTurnAroundTime = 0;
    int totalWaitTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n)
    {
        int nextProcessIndex = findNextProcess(proc, n, currentTime);

        if (nextProcessIndex == -1)
        {
            currentTime++;
            continue;
        }

        Process *p = &proc[nextProcessIndex];
        if (currentTime < p->arrivalTime)
        {
            currentTime = p->arrivalTime;
        }
        p->waitTime = currentTime - p->arrivalTime;
        p->completionTime = currentTime + p->burstTime;
        p->turnAroundTime = p->completionTime - p->arrivalTime;
        p->isCompleted = 1;

        currentTime = p->completionTime;

        totalTurnAroundTime += p->turnAroundTime;
        totalWaitTime += p->waitTime;
        completedProcesses++;
    }

    // Print Process Details
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].completionTime, proc[i].waitTime, proc[i].turnAroundTime);
    }

    // Print Average Times
    printf("Average Wait Time: %.2f\n", (float)totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);
}

void printGanttChart(Process proc[], int n)
{
    printf("\nThe Gantt chart for the given jobs is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", proc[i].pid);
        if (i < n - 1)
        {
            printf("| ");
        }
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
        proc[i].isCompleted = 0;
    }

    sortProcessesByArrival(proc, n);
    calculateTimes(proc, n);
    printGanttChart(proc, n);

    return 0;
}
