#include <iostream>
#include <vector>
#include <unordered_set>
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

int fifoPageReplacement(vector<int> &pages, vector<int> &frames)
{
    unordered_set<int> st;
    int frameSize = frames.size();
    int frameIndex = 0;
    int miss = 0;
    for (const int &page : pages)
    {
        if (st.find(page) == st.end()) // not found == miss
        {
            st.erase(frames[frameIndex]); // remove the page in fifo manner => the curr frameindex points to the first pushed page in the frame
            st.insert(page);
            frames[frameIndex] = page;
            frameIndex = (frameIndex + 1) % frameSize;
            ++miss;
            cout << "Miss " << page << ": ";
            displayFrame(frames);
        }
        else
        {
            cout << "Hit " << page << ": ";
            displayFrame(frames);
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

    vector<int> pages(n);
    vector<int> frames(m, -1); // initialized vector with -1 to indicate empty frames

    cout << "Enter the page reference sequence seperated by space: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> pages[i];
    }
    int pageFaults = fifoPageReplacement(pages, frames);
    cout << endl;
    cout << "Total pageFaults : " << pageFaults << endl;
    return 0;
}