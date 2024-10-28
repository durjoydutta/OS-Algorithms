#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void sstfDiskSchedule(int start, vector<int> &references)
{
    int currPos = start;
    int size = references.size();
    unordered_set<int> finished;
    int totalMoves = 0;

    for (int i = 0; i < size; ++i)
    {
        int minMoves = INT_MAX;
        int nextPos;
        for (const int &pos : references)
        {
            int moves = abs(pos - currPos);
            if (finished.find(pos) == finished.end() && moves < minMoves)
            {
                minMoves = moves;
                nextPos = pos;
            }
        }
        cout << nextPos << " : " << minMoves << " moves" << endl;
        finished.insert(nextPos);
        totalMoves += minMoves;
        currPos = nextPos;
    }
    cout << "Total Moves: " << totalMoves << endl;
}

int main()
{
    int start, N;
    cout << "/////FCFS Disk Scheduling Algorithm/////" << endl;

    cout << "Enter the head start position: ";
    cin >> start;
    cout << "Enter the number of disk references: ";
    cin >> N;

    vector<int> references(N, 0);

    cout << "Enter the references in order seperated by space : ";
    for (int i = 0; i < N; i++)
    {
        cin >> references[i];
    }

    sstfDiskSchedule(start, references);

    return 0;
}