#include "fourteen.h"


void fourteen::solve()
{
    const string INPUT_FILE = "../input/14.txt";
    const string OUTPUT_FILE = "../output/14.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    unsigned long result1 = getTotalLoadNorth(input);

    spinCycle(input, 1000000000);
    unsigned long result2 = getTotalLoad(input);

    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved fourteen " << result1 << ":" << result2 << endl;

}

unsigned long fourteen::getTotalLoadNorth(const vector<string>& rocks)
{
    unsigned long result = 0;
    for(int j = 0; j < rocks[0].length(); j++)
    {
        unsigned long pin = rocks.size();
        for(int i = 0; i < rocks.size(); i++)
        {
            if(rocks[i][j] == 'O')
            {
                result += pin--;
            }
            else if(rocks[i][j] == '#')
            {
                pin = rocks.size() - i - 1;
            }
        }
    }
    return result;
}

unsigned long fourteen::getTotalLoad(const vector<string>& rocks)
{
    unsigned long result = 0;
    for(int i = 0; i < rocks.size(); i++)
    {
        for(int j = 0; j < rocks[i].length(); j++)
        {
            if(rocks[i][j] == 'O') result += rocks.size() - i;
        }
    }
    return result;
}

void fourteen::spinCycle(vector<string>& rocks, int numCycles)
{
    int cycleStart = -1;
    int cycleEnd = -1;
    unordered_map<size_t, vector<string>> cache;
    vector<vector<string>*> cacheList;
    int pin;
    int i;
    int j;
    for(int n = 0; n < numCycles; n++)
    {
        //north
        for(j = 0; j < rocks[0].length(); j++)
        {
            pin = 0;
            for(i = 0; i < rocks.size(); i++)
            {
                if(rocks[i][j] == 'O')
                {
                    rocks[i][j] = '.';
                    rocks[pin++][j] = 'O';
                }
                else if(rocks[i][j] == '#')
                {
                    pin = i+1;
                }
            }

        }

        //west
        for(i = 0; i < rocks.size(); i++)
        {
            pin = 0;
            for(j = 0; j < rocks.size(); j++)
            {
                if(rocks[i][j] == 'O')
                {
                    rocks[i][j] = '.';
                    rocks[i][pin++] = 'O';
                }
                else if(rocks[i][j] == '#')
                {
                    pin = j+1;
                }
            }
        }
        //south
        for(j = 0; j < rocks[0].length(); j++)
        {
            pin = rocks.size() - 1;
            for(i = rocks.size() - 1; i >= 0; i--)
            {
                if(rocks[i][j] == 'O')
                {
                    rocks[i][j] = '.';
                    rocks[pin--][j] = 'O';
                }
                else if(rocks[i][j] == '#')
                {
                    pin = i-1;
                }
            }

        }


        //east
        for(i = 0; i < rocks.size(); i++)
        {
            pin = rocks.size() - 1;
            for(j = rocks.size() - 1 ; j >= 0; j--)
            {
                if(rocks[i][j] == 'O')
                {
                    rocks[i][j] = '.';
                    rocks[i][pin--] = 'O';
                }
                else if(rocks[i][j] == '#')
                {
                    pin = j-1;
                }
            }
        }


        size_t newHash = rocksHash(rocks);
        if (cache.count(newHash))
        {
            if (cycleStart == -1) {cycleStart = n; cout << "START " << cycleStart << endl;}
            else if(rocks == *cacheList[cycleStart] && cycleEnd == -1)
            {
                cycleEnd = n;
                rocks = *cacheList[cycleStart + ((numCycles - cycleStart) % (cycleEnd - cycleStart))-1];
                return;
            }
        }
        std::cout << n << " " << getTotalLoad(rocks) << endl;
        cache[newHash] = rocks;
        cacheList.push_back(&cache[newHash]);
    }

}

size_t fourteen::rocksHash(const vector<string>& rocks)
{
    std::hash<char> hasher;
    size_t hashVal = 0;
    for(auto row : rocks)
    {
        for(auto c : row)
        {
            hashVal ^= hasher(c) + 0x9e3779b9 + (hashVal << 6) + (hashVal >> 2);
        }
    }
    return hashVal;
}
