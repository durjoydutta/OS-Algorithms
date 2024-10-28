#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool dfs(int u, unordered_map<int, vector<int>> &adjList, vector<int> &visited)
{
    visited[u] = 0; // visiting
    for (int &v : adjList[u])
    {
        if (visited[v] == -1 && dfs(v, adjList, visited))
            return true;
        else if (visited[v] == 0)
            return true;
    }
    visited[u] = 1; // visited
    return false;
}

bool isCyclic(unordered_map<int, vector<int>> &adjList, int N)
{
    vector<int> visited(N, -1);
    for (const auto &it : adjList)
    {
        int u = it.first;
        if (visited[u] == -1 && dfs(u, adjList, visited))
            return true;
    }
    return false;
}

bool willCreateCycle(unordered_map<int, vector<int>> &adjList, int from, int to, int N)
{
    adjList[from].push_back(to);
    bool flag = isCyclic(adjList, N);
    adjList[from].pop_back();
    return flag;
}

int main()
{
    int numProcesses, numResources, numEdges;
    int p0 = 0;   // first process id
    int r0 = 100; // first resource id
    cout << "INPUT:" << endl;
    cout << "Enter no. of processes, no. of resources, no. of edges separated by space: ";
    cin >> numProcesses >> numResources >> numEdges;

    int N = max(p0 + numProcesses, r0 + numResources) + 1;
    unordered_map<int, vector<int>> adjList;
    cout << "Enter the edge list of the graph: " << endl;
    for (int i = 0; i < numEdges; ++i)
    {
        int from, to;
        cin >> from >> to;
        adjList[from].push_back(to);
    }

    // Check for cycles (deadlock detection)
    cout << "\nOUTPUT:" << endl;
    if (isCyclic(adjList, N))
    {
        cout << "Cycle is present. Deadlocked" << endl;
    }
    else
    {
        cout << "Not deadlocked" << endl;

        // Check if adding a claim edge will create a cycle
        int claimFrom, claimTo;
        cout << "Enter the claim edge (from to): ";
        cin >> claimFrom >> claimTo;

        if (willCreateCycle(adjList, claimFrom, claimTo, N))
        {
            cout << "Adding this claim edge will create a deadlock" << endl;
        }
        else
        {
            cout << "Adding this claim edge will NOT create a deadlock" << endl;
        }
    }

    return 0;
}