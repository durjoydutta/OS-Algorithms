#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int fifoPageReplacement(vector<int> &pages, vector<int> &frames)
{
    int frameSize = frames.size();
    int frameIndex = 0;
    int miss = 0;

    for (const int &page : pages)
    {
        bool pageFound = false;
        for (const int &frame : frames)
        {
            if (frame == page)
            {
                pageFound = true;
                break;
            }
        }
        if (!pageFound)
        {
            frames[frameIndex] = page;
            frameIndex = (frameIndex + 1) % frameSize;
            ++miss;
        }
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

    vector<int> pages;
    vector<int> frames(m, -1); // initialized vector with -1 to indicate empty frames

    cout << "Enter the page reference sequence seperated by space: ";
    for (int i = 0; i < n; ++i)
    {
        int page;
        cin >> page;
        pages.push_back(page);
    }
    int pageFaults = fifoPageReplacement(pages, frames);
    cout << pageFaults << endl;
    return 0;
}