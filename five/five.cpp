#include "five.h"

void five::solve()
{
    const string INPUT_FILE = "../input/5.txt";
    const string OUTPUT_FILE = "../output/5.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    unsigned long result1 = UINT64_MAX;
    unsigned long result2 = 0;

    vector<unsigned long> seeds;
    vector<vector<vector<unsigned long>>> maps;

    parseSeeds(input[0], seeds);
    parseMap(input, maps);

    for (auto &seed : seeds)
    {
        result1 = min(getLocation(maps, seed), result1);
    }

    vector<thread> threads;

    for (int i = 0; i < seeds.size(); i += 2)
    {
        threads.push_back(thread(getLocRange, maps, seeds[i], seeds[i+1]));
    }

    for(auto& t : threads) t.join();

    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved five " << result1 << ":" << result2 << endl;
}

void five::parseSeeds(const string &seedStr, vector<unsigned long> &seeds)
{
    int idx = seedStr.find(":") + 2;
    while (idx < seedStr.length())
    {
        unsigned long val = 0;
        while (isdigit(seedStr[idx]))
        {
            val *= 10;
            val += (seedStr[idx] - '0');
            idx++;
        }
        seeds.push_back(val);
        idx++;
    }
}

void five::parseMap(const vector<string> &input, vector<vector<vector<unsigned long>>> &maps)
{
    int idx = 3;
    while (idx < input.size())
    {
        vector<vector<unsigned long>> map;
        while (idx < input.size() && input[idx].length() > 0)
        {
            map.push_back(vector<unsigned long>(3, 0));

            int lineIdx = 0;
            int valIdx = 0;
            while (lineIdx < input[idx].length())
            {
                unsigned long val = 0;
                while (lineIdx < input[idx].length() && input[idx][lineIdx] != ' ')
                {
                    val *= 10;
                    val += input[idx][lineIdx++] - '0';
                }
                lineIdx++;
                map.back()[valIdx++] = val;
            }
            idx++;
        }
        idx += 2;
        maps.push_back(map);
    }
}

unsigned long five::getLocation(const vector<vector<vector<unsigned long>>> &maps, unsigned long seed)
{
    unsigned long destination = seed;
    for (auto &map : maps)
    {
        for (auto &range : map)
        {
            if (destination >= range[1] && (destination < range[1] + range[2]))
            {
                destination = range[0] + (destination - range[1]);
                break;
            }
        }
    }
    return destination;
}

void five::getLocRange(const vector<vector<vector<unsigned long>>> &maps, unsigned long seed, unsigned long range)
{
    unsigned long theResult = UINT64_MAX;
    for (unsigned long j = 0; j < range; j++)
    {
        theResult = min(getLocation(maps, seed + j), theResult);
    }
    std::cout << "Min: " << theResult << endl;

}