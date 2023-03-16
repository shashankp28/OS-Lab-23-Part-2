#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void read_file(vector<int> &requests)
{
    ifstream infile("req1.dat");
    int num;
    while (infile >> num)
    {
        requests.push_back(num);
    }
    infile.close();
}

int index(vector<int> &requests, int num){
    for (int i = 0; i < requests.size(); i++){
        if(requests[i] == num)
            return i;
    }
    return -1;
}

int get_opt_request(vector<int> &requests, unordered_set<int> &memory_frames)
{
    int max_index = INT_MIN, swap_request = -1;
    for(auto i : memory_frames){
        int swap_index = index(requests, i);
        if(swap_index==-1)
            continue;
        if(max_index<swap_index){
            max_index = swap_index;
            swap_request = requests[swap_index];
        }
    }
    if(max_index==INT_MIN)
        return requests[0];
    else
        return max_index;
}

int main()
{
    int addressable_size = 60;
    int memory_size = 20;
    int disk_size = 60;
    int pageFaults = 0;

    vector<int> requests;
    read_file(requests);

    unordered_set<int> memory_frames;

    int ind = 0;
    for (auto i : requests)
    {
        if (memory_frames.find(i) != memory_frames.end())
            continue;

        pageFaults++;
        if (memory_frames.size() >= memory_size)
        {
            int req = get_opt_request(requests, memory_frames);
            memory_frames.erase(req);
        }
        memory_frames.insert(i);
    }

    cout << "Page Faults " << pageFaults << "\n";
    cout << "Total " << requests.size() << "\n";

    return 0;
}