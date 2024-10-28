#include <iostream>
#include <vector>
using namespace std;

bool isSafeState(int n, int m, vector<int> &Available,
                 vector<vector<int>> &Max, vector<vector<int>> &Allocation)
{
    vector<vector<int>> Need(n, vector<int>(m));
    vector<bool> Finish(n, false);
    vector<int> Work = Available;

    // calculate the Need matrix
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

                // if a process can be allocated resources
                if (canAllocate)
                {
                    // simulate the allocation
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

    if (isSafeState(n, m, Available, Max, Allocation))
    {
        cout << "The system is in a safe state." << endl;
    }
    else
    {
        cout << "The system is not in a safe state." << endl;
    }

    return 0;
}
