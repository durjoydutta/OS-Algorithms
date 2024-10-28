#include <iostream>
#include <vector>
using namespace std;

bool isSafeState(int n, int m, vector<int> Available, vector<vector<int>> &Max, vector<vector<int>> &Need, vector<vector<int>> &Allocation)
{
    vector<bool> finished(m);

    while (true)
    {
        bool foundProcess = false;
        for (int i = 0; i < n; ++i)
        {
            bool canAllocate = true;
            if (!finished[i])
            {
                for (int j = 0; j < m; ++j)
                {
                    if (Need[i][j] > Available[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < m; ++j)
                    {
                        Available[j] += Allocation[i][j];
                        finished[i] = true;
                    }
                }
            }
        }
        if (!foundProcess)
            break;
    }

    for (int i = 0; i < n; ++i)
    {
        if (!finished[i])
            return false;
    }

    return true;
}

bool requestResources(int n, int m, vector<int> &Available, vector<vector<int>> &Max,
                      vector<vector<int>> &Allocation, vector<vector<int>> &Need, vector<int> Request, int processId)
{
    for (int j = 0; j < m; ++j)
    {
        if (Request[j] > Need[processId][j])
        {
            cout << "Requesting more than need! " << endl;
            return false;
        }
        if (Request[j] > Available[j])
        {
            cout << "Requesting more than available! " << endl;
            return false;
        }
        for (int j = 0; j < m; ++j)
        {
            Need[processId][j] -= Request[j];
            Available[j] -= Request[j];
            Allocation[processId][j] += Request[j];
        }
    }

    if (isSafeState(n, m, Available, Max, Need, Allocation))
    {
        cout << "In safe state after fulfilling request." << endl;
        return true;
    }

    cout << "Not in safe state after fulfilling request" << endl;
    return false;
}

int main()
{
    int n = 5; // Number of processes
    int m = 4; // Number of resource types

    // Arbitrary Available vector (number of available instances of each resource)
    vector<int> Available = {3, 2, 1, 1};

    // Arbitrary Max matrix (maximum demand of each process)
    vector<vector<int>> Max = {
        {6, 0, 1, 2},
        {2, 7, 5, 0},
        {2, 3, 5, 6},
        {1, 6, 5, 3},
        {1, 6, 5, 6}};

    // Arbitrary Allocation matrix (currently allocated resources to each process)
    vector<vector<int>> Allocation = {
        {4, 0, 0, 1},
        {1, 1, 0, 0},
        {1, 2, 5, 4},
        {0, 6, 3, 3},
        {0, 2, 1, 2}};

    vector<vector<int>> Need(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    if (isSafeState(n, m, Available, Max, Need, Allocation))
    {
        cout << "The system is in a safe state." << endl;
    }
    else
    {
        cout << "The system is not in a safe state." << endl;
    }
    return 0;
}