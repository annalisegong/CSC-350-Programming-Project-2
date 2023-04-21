#include <iostream>
using namespace std;

void bestFit(int freeMemory[], int n, int blockSize[], int b)
{
    cout << "Best Fit Allocation" << endl;
    //create physical memory of 50 blocks
    int physicalMemory[50];
    //initialize all blocks as empty where each block has value of -1
    for (int i = 0; i < b; i++)
    {
        physicalMemory[i] = -1;
    }

    double allocated = 0;
    //tracks memory utilization for each step/new request
    double memoryUsed[64];
    //initiallize all as NULL prior to any request
    for(int i = 0; i < n; i++)
    {
        memoryUsed[i] = NULL;
    }
    //pick each process and find suitable blocks according to its size and assign to it
    for(int i = 0; i < b; i ++)
    {
        int bestIndex = -1;
        for(int j = 0; j < n; j++)
        {
            if(freeMemory[j] >= blockSize[i])
            {
                //finds smallest memory block to allocate new block
                if(bestIndex == -1)
                {
                    bestIndex = j;
                }
                else if(freeMemory[bestIndex] > freeMemory[j])
                {
                    bestIndex = j;
                }
            }
        }

        //if block could be allocated in memory
        if(bestIndex != -1)
        {
            allocated = allocated + 1;
            physicalMemory[i] = bestIndex;
            //reduce available memory
            freeMemory[bestIndex] -= blockSize[i]; 
        }

        //update memory utilization for each new block request/'step'
        memoryUsed[i] =  double(allocated) / double(n);

        //search time
        if (physicalMemory[i] != -1)
            cout << "block " << i << " search time: " << physicalMemory[i] + 1;
        else
            cout << "Block " << i << " was not allocated";
        cout << endl;
    }
    //calculate average memory utilization
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        if(memoryUsed[i] != NULL)
        {
            sum = sum + memoryUsed[i];
        }
    }
    double avgMemoryUsed = sum / b;
    cout << "Average: " << avgMemoryUsed * 100 << " %" << endl;
    cout << endl;
}

void worstFit(int freeMemory[], int n, int blockSize[], int b)
{
    cout << "Worst Fit Allocation" << endl;
    int physicalMemory[50];
    //initialize all blocks as empty where each block has value of -1
    for (int i = 0; i < b; i++)
    {
        physicalMemory[i] = -1;
    }

    double allocated = 0;
    double memoryUsed[64];
    for(int i = 0; i < n; i++)
    {
        memoryUsed[i] = NULL;
    }

    for(int i = 0; i < b; i++)
    {
        int worstIndex = -1;
        for(int j = 0; j < n; j++)
        {
            if(freeMemory[j] >= blockSize[i])
            {
                //implement search time (j is the number of searches?)
                if(worstIndex == -1)
                {
                    worstIndex = j;
                }
                else if(freeMemory[worstIndex] < freeMemory[j])
                {
                    worstIndex = j;
                }
            }
        }
        //if block allocated, update physical memory and reduce size of freeMemory block
        if(worstIndex != -1)
        {
            allocated = allocated + 1;
            physicalMemory[i] = worstIndex;
            freeMemory[worstIndex] -= blockSize[i];
        }
        //track memory utilization for each new block request/'step'
        memoryUsed[i] =  double(allocated) / double(n);

        //search time
        if (physicalMemory[i] != -1)
            cout << "block " << i << " search time: " << physicalMemory[i] + 1;
        else
            cout << "Block " << i << " was not allocated";
        cout << endl;
    }
    //calculate average memory utilization
    double sum = 0;
    for(int i = 0; i < n; i++)
    {
        if(memoryUsed[i] != NULL)
        {
            sum = sum + memoryUsed[i];
        }
    }
    double avgMemoryUsed = sum / b;
    cout << "Average: " << avgMemoryUsed * 100 << " %" << endl;
    cout << endl;    
}

int main()
{
    //tracks size of each block in memory
    int freeMemory[64];
    int f;
    //determines size of open blocks in memory
    cout << "free memory { ";
    for (int i = 0; i < 64; i++)
    {
        f = (rand() % 6 + 1);
        freeMemory[i] = f;
        cout << freeMemory[i] << ", ";
    }
    cout << "}" << endl;
    cout << endl;

    //tracks size of the 50 new block requests
    int blockSize[50];
    int minS = 1;
    int maxS = 8;
    int s;
    //determine new request block's size (between 1 and 8)
    cout << "block size { ";
    for(int i = 0; i < 50; i ++)
    {
        s = (rand() % 8 + 1);
        //add random block size for each request
        blockSize[i] = s;
        cout << blockSize[i] << ", ";
    }
    cout << "}" << endl;
    cout << endl;

    int n = sizeof(freeMemory) / sizeof(freeMemory[0]);
    int b = sizeof(blockSize) / sizeof(blockSize[0]);

    bestFit(freeMemory, n, blockSize, b);
    worstFit(freeMemory, n, blockSize, b);

    return 0;
}