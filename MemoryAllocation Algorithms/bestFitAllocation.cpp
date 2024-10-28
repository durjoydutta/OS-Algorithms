#include <iostream>
#include <vector>
#include <map>
using namespace std;

void bestFitAlloc(vector<int> &blocks, vector<int> &processes,
                  map<int, int> &allocMap)
{
    int P = processes.size();
    int M = blocks.size();
    for (int i = 0; i < P; ++i)
    {
        int pSize = processes[i];
        bool allocated = false;
        int minBlockSize = INT_MAX;
        int bestFitIndex = -1;
        for (int j = 0; j < M; ++j)
        {
            int &bSize = blocks[j];
            if (bSize < minBlockSize && pSize <= bSize)
            {
                minBlockSize = bSize;
                bestFitIndex = j;
            }
        }
        if (bestFitIndex != -1)
        {
            allocMap[i] = bestFitIndex;
            blocks[bestFitIndex] -= pSize;
        }
        else
            allocMap[i] = -1;
    }
}

void printAllocMap(vector<int> &ogBlocks, vector<int> &occupiedBlocks, vector<int> &processes,
                   map<int, int> &allocMap)
{
    cout << "\n\t\t///Best Fit Allocation///" << endl;
    cout << "\nProcess No.\tProcess Size\tBlock No.\tBlock Size\tInternalFragmentation\n";
    for (const pair<int, int> &it : allocMap)
    {
        int pId = it.first;
        int bId = it.second;
        int pSize = processes[pId];

        if (bId != -1)
            cout << pId + 1 << "\t\t" << pSize << "\t\t" << bId + 1 << "\t\t" << ogBlocks[bId] << "\t\t" << occupiedBlocks[bId] << endl;
        else
            cout << pId + 1 << "\t\t" << pSize << "\t\t" << "---" << "\t\t" << "---" << "\t\t" << "---" << endl;
    }
}

int main()
{
    int bNum, pNum;

    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> processes = {212, 417, 112, 426};
    vector<int> blockCopy = blocks;
    map<int, int> processAllocationMap; // to map the process id with its allocated block number (if unallocated -1 is stored)

    bestFitAlloc(blockCopy, processes, processAllocationMap);
    printAllocMap(blocks, blockCopy, processes, processAllocationMap);

    return 0;
}