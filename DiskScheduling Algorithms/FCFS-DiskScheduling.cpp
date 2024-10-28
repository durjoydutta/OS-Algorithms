#include <iostream>
#include <vector>
using namespace std;

void fcfsDiskSchedule(int start, vector<int> &references)
{
    int totalMoves = 0;
    int currPos = start;
    for (const int &nextPos : references)
    {
        int moves = abs(nextPos - currPos);
        totalMoves += moves;
        currPos = nextPos;
        cout << nextPos << " : " << moves << " moves" << endl;
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

    fcfsDiskSchedule(start, references);

    return 0;
}