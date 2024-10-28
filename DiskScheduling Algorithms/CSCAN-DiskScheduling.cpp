#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int totalMoves = 0;

void schedule(int &currPos, vector<int> arr, int low, int high, int dir)
{
    int nextPos, moves;

    if (dir == -1)
    {
        for (int i = high; i >= low; --i)
        {
            nextPos = arr[i];
            moves = abs(nextPos - currPos);
            cout << nextPos << " : " << moves << " moves" << endl;
            totalMoves += moves;
            currPos = nextPos;
        }
    }
    else
    {
        for (int i = low; i <= high; ++i)
        {
            nextPos = arr[i];
            moves = abs(nextPos - currPos);
            cout << nextPos << " : " << moves << " moves" << endl;
            totalMoves += moves;
            currPos = nextPos;
        }
    }
}

void cscanDiskSchedule(int start, vector<int> references, string &dir, int lower, int upper)
{
    references.push_back(start);
    references.push_back(lower);
    references.push_back(upper);

    int high = references.size() - 1;

    sort(references.begin(), references.end());
    int startPos = find(references.begin(), references.end(), start) - references.begin();

    int currPos = start;
    int rebound = std::abs(upper - lower); // the moves between upper and lower
    if (dir == "left")
    {
        schedule(currPos, references, 0, startPos - 1, -1);
        cout << upper << " : " << rebound << " moves" << endl;
        schedule(upper, references, startPos + 1, high - 1, -1);
    }
    else if (dir == "right")
    {
        schedule(currPos, references, startPos + 1, high, 1);
        cout << lower << " : " << rebound << " moves" << endl;
        schedule(lower, references, 1, startPos - 1, 1);
    }
    totalMoves += rebound;
    cout << "Total Moves: " << totalMoves << endl;
}

int main()
{
    int start, N, lower, upper;
    string dir;

    cout << "/////C-SCAN Disk Scheduling Algorithm/////" << endl;

    cout << "\nEnter the lower and upper limit separated by space: ";
    cin >> lower >> upper;

    cout << "Enter the head start position: ";
    cin >> start;

    cout << "\nEnter initial head movement direction (only enter 'left' or 'right'): ";
    cin >> dir;
    if (dir != "left" && dir != "right")
    {
        cerr << "Please try again by entering a valid direction" << endl;
        return -1;
    }

    cout << "Enter the number of disk references: ";
    cin >> N;

    vector<int> references(N, 0);

    cout << "Enter the references in order seperated by space : ";
    for (int i = 0; i < N; i++)
    {
        cin >> references[i];
    }

    cscanDiskSchedule(start, references, dir, lower, upper);

    return 0;
}