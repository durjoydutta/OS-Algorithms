#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void displayFrame(vector<int> &frames)
{
    for (const int &frame : frames)
    {
        if (frame == -1)
            cout << "- ";
        else
            cout << frame << " ";
    }
    cout << endl;
}

int findLruIndex(unordered_map<int, int> &umap, vector<int> &frames)
{
    int frameSize = frames.size();
    if (umap.size() < frameSize)
        return umap.size();

    int minVal = INT_MAX;
    int lruIndex;
    for (int i = 0; i < frameSize; ++i)
    {
        int page = frames[i];
        if (umap[page] < minVal)
        {
            minVal = umap[page];
            lruIndex = i;
        }
    }
    return lruIndex;
}

int lruPageReplacement(vector<int> &pages, vector<int> &frames)
{
    unordered_map<int, int> umap;
    int pageSize = pages.size();
    int frameSize = frames.size();
    int lruIndex = 0;
    int miss = 0;
    for (int i = 0; i < pageSize; ++i)
    {
        int page = pages[i];
        if (umap.find(page) == umap.end()) // indicates a miss
        {
            lruIndex = findLruIndex(umap, frames);
            umap.erase(frames[lruIndex]);
            frames[lruIndex] = page;
            ++miss;
            cout << "Miss " << page << ": ";
        }
        else
            cout << "Hit " << page << ": ";
        umap[page] = i;
        displayFrame(frames);
    }

    return miss;
}

int main()
{
    int n, m; // length of reference sequence and frame size
    cout << "Enter the number of pages in the reference sequence : ";
    cin >> n;
    cout << "Enter the page frame size: ";
    cin >> m;

    vector<int> pages(n);
    vector<int> frames(m, -1); // initialized vector with -1 to indicate empty frames

    cout << "Enter the page reference sequence seperated by space: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> pages[i];
    }
    int pageFaults = lruPageReplacement(pages, frames);
    cout << endl;
    cout << "Total pageFaults : " << pageFaults << endl;
    return 0;
}