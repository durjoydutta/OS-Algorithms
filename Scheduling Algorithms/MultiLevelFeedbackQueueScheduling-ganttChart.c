#include <stdio.h>
#include <stdbool.h>

#define NUM_QUEUES 3

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

typedef struct
{
    Process *processes[100];
    int front;
    int rear;
} Queue;

void enqueue(Queue *q, Process *p)
{
    q->processes[q->rear++] = p;
}

Process *dequeue(Queue *q)
{
    if (q->front == q->rear)
    {
        return NULL;
    }
    return q->processes[q->front++];
}

bool isEmpty(Queue *q)
{
    return q->front == q->rear;
}

void initializeQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

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

void calculateTimes(Process proc[], int n, int timeQuantums[])
{
    int currentTime = 0;
    int completed = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int ganttChart[1000];
    int ganttSize = 0;
    Queue queues[NUM_QUEUES];

    for (int i = 0; i < NUM_QUEUES; i++)
    {
        initializeQueue(&queues[i]);
    }

    enqueue(&queues[0], &proc[0]);
    bool isInQueue[n];
    for (int i = 0; i < n; i++)
    {
        isInQueue[i] = false;
    }
    isInQueue[0] = true;

    while (completed != n)
    {
        bool executed = false;

        for (int i = 0; i < NUM_QUEUES; i++)
        {
            Process *p = dequeue(&queues[i]);
            if (p != NULL)
            {
                executed = true;
                if (ganttSize == 0 || ganttChart[ganttSize - 1] != p->pid)
                {
                    ganttChart[ganttSize++] = p->pid;
                }

                int execTime = (p->remainingTime < timeQuantums[i]) ? p->remainingTime : timeQuantums[i];
                p->remainingTime -= execTime;
                currentTime += execTime;

                if (p->remainingTime == 0)
                {
                    p->completionTime = currentTime;
                    p->turnaroundTime = p->completionTime - p->arrivalTime;
                    p->waitTime = p->turnaroundTime - p->burstTime;

                    totalWaitTime += p->waitTime;
                    totalTurnaroundTime += p->turnaroundTime;

                    completed++;
                }
                else
                {
                    if (i < NUM_QUEUES - 1)
                    {
                        enqueue(&queues[i + 1], p);
                    }
                    else
                    {
                        enqueue(&queues[i], p);
                    }
                }

                // Enqueue new processes that have arrived by the current time
                for (int j = 0; j < n; j++)
                {
                    if (!isInQueue[j] && proc[j].arrivalTime <= currentTime)
                    {
                        enqueue(&queues[0], &proc[j]);
                        isInQueue[j] = true;
                    }
                }

                break;
            }
        }

        if (!executed)
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

    int timeQuantums[NUM_QUEUES];
    for (int i = 0; i < NUM_QUEUES; i++)
    {
        printf("Enter the time quantum for queue %d: ", i + 1);
        scanf("%d", &timeQuantums[i]);
    }

    sortProcessesByArrivalTime(proc, n);
    calculateTimes(proc, n, timeQuantums);

    return 0;
}
