#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void displayWaitForGraph(int p0, int r0, int numProcesses, int numResources,
                         vector<pair<int, int>> &requestEdges, vector<pair<int, int>> &allocationEdges)
{
    cout << "Processes: ";
    for (int i = p0; i < p0 + numProcesses; ++i)
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "Resources: ";
    for (int i = r0; i < r0 + numProcesses; ++i)
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "Request Edges : " << endl;
    for (const auto &it : requestEdges)
    {
        cout << it.first << " " << it.second << endl;
    }
    cout << endl;

    cout << "Allocation Edges : " << endl;
    for (const auto &it : allocationEdges)
    {
        cout << it.first << " " << it.second << endl;
    }
    cout << endl;

    // wait for graph
    cout << "Wait-For Edges: " << endl;
    for (const auto &i : requestEdges)
    {
        int p_i = i.first;
        int rq = i.second;

        for (const auto &j : allocationEdges)
        {
            int p_j = j.second;
            if (j.first == rq)
            {
                cout << p_i << " " << p_j << endl;
            }
        }
    }
}

int main()
{
    int numProcesses, numResources, numEdges;
    int p0 = 0;   // first process id
    int r0 = 100; // first resource id
    cout << "INPUT:" << endl;
    cout << "Enter no. of processes, no. of resources, no. of edges seperated by space: ";
    cin >> numProcesses >> numResources >> numEdges;

    vector<pair<int, int>> requestEdges;
    vector<pair<int, int>> allocationEdges;
    cout << "Enter the edge list of the graph: " << endl;

    for (int i = 0; i < numEdges; ++i)
    {
        int from, to;
        cin >> from >> to;

        if (from >= p0 && from < p0 + numResources && to >= r0 && to < r0 + numResources)
        {
            requestEdges.push_back({from, to});
        }

        if (from >= r0 && from < r0 + numResources && to >= p0 && to < p0 + numResources)
        {
            allocationEdges.push_back({from, to});
        }
    }

    // display graph
    cout << "\nOUTPUT:" << endl;
    displayWaitForGraph(p0, r0, numProcesses, numResources, requestEdges, allocationEdges);

    return 0;
}