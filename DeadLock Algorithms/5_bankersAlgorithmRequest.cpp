#include <iostream>
#include <vector>
using namespace std;

bool isSafeState(int n, int m, vector<int> &Available,
                 vector<vector<int>> &Max, vector<vector<int>> &Allocation)
{
    vector<vector<int>> Need(n, vector<int>(m));
    vector<bool> Finish(n, false);
    vector<int> Work = Available;

    // Calculate the Need matrix
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    // Safety algorithm
    while (true)
    {
        bool foundProcess = false;
        for (int i = 0; i < n; ++i)
        {
            if (!Finish[i])
            {
                // Check if Need[i] <= Work
                bool canAllocate = true;
                for (int j = 0; j < m; ++j)
                {
                    if (Need[i][j] > Work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                // If a process can be allocated resources
                if (canAllocate)
                {
                    // Simulate the allocation
                    for (int j = 0; j < m; ++j)
                    {
                        Work[j] += Allocation[i][j];
                    }
                    Finish[i] = true;
                    foundProcess = true;
                }
            }
        }

        // If no process was found in this iteration, break the loop
        if (!foundProcess)
        {
            break;
        }
    }
    // check if all processes have been finished
    for (const auto &i : Finish)
        if (!i)
            return false; // not in safe state
    return true;          // In a safe state
}

bool requestResources(int n, int m, vector<int> &Available, vector<vector<int>> &Max,
                      vector<vector<int>> &Allocation, vector<int> Request, int processId)
{
    vector<vector<int>> Need(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    // Step 1: Check if Request <= Need
    for (int j = 0; j < m; ++j)
    {
        if (Request[j] > Need[processId][j])
        {
            cout << "Error: Process has exceeded its maximum claim." << endl;
            return false;
        }
    }

    // Step 2: Check if Request <= Available
    for (int j = 0; j < m; ++j)
    {
        if (Request[j] > Available[j])
        {
            cout << "Process " << processId << " must wait: Resources are not available." << endl;
            return false;
        }
    }

    // Step 3: Pretend to allocate requested resources
    for (int j = 0; j < m; ++j)
    {
        Available[j] -= Request[j];
        Allocation[processId][j] += Request[j];
        Need[processId][j] -= Request[j];
    }

    // Check if the system is in a safe state
    if (isSafeState(n, m, Available, Max, Allocation))
    {
        cout << "The system remains in a safe state after the request by process " << processId << "." << endl;
        return true;
    }
    else
    {
        // Rollback allocation (can be skipped)
        for (int j = 0; j < m; ++j)
        {
            Available[j] += Request[j];
            Allocation[processId][j] -= Request[j];
            Need[processId][j] += Request[j];
        }
        cout << "The system would be unsafe after the request by process " << processId << ". Request denied." << endl;
        return false;
    }
}

int main()
{
    int n = 3; // Number of processes
    int m = 3; // Number of resources (X, Y, Z)

    // Arbitrary Available vector (number of available instances of each resource)
    vector<int> Available = {3, 3, 2};

    // Arbitrary Max matrix (maximum demand of each process)
    vector<vector<int>> Max = {
        {8, 4, 3}, // P0
        {6, 2, 0}, // P1
        {3, 3, 3}  // P2
    };

    // Arbitrary Allocation matrix (currently allocated resources to each process)
    vector<vector<int>> Allocation = {
        {0, 0, 1}, // P0
        {3, 2, 0}, // P1
        {2, 1, 1}  // P2
    };

    // Requests
    vector<int> REQ1 = {0, 0, 2}; // P0 requests 0 units of X, 0 units of Y, and 2 units of Z
    vector<int> REQ2 = {2, 0, 0}; // P1 requests 2 units of X, 0 units of Y, and 0 units of Z

    // Check for REQ1
    cout << "Checking REQ1 (P0 requests 0 units of X, 0 units of Y, and 2 units of Z):" << endl;
    requestResources(n, m, Available, Max, Allocation, REQ1, 0);

    // Check for REQ2
    cout << "\nChecking REQ2 (P1 requests 2 units of X, 0 units of Y, and 0 units of Z):" << endl;
    requestResources(n, m, Available, Max, Allocation, REQ2, 1);

    return 0;
}
