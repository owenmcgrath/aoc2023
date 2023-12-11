#include "eleven.h"

void eleven::solve()
{

    // get i/o file handles
    ofstream output("../output/11.txt");

    vector<string> space;
    set<int> emptySpaceRows;
    set<int> emptySpaceCols;
    vector<pair<int,int>> galaxies;
    ifstream inHandle("../input/11.txt");
    string line;
    if(inHandle.is_open())
    {
        int i = 0;
        while(getline(inHandle, line))
        {
            space.push_back(line);
            size_t galPos = line.find('#');
            if(galPos == string::npos) 
            {
                emptySpaceRows.insert(i);
            }
            else while(galPos != string::npos)
            {
                galaxies.push_back(make_pair(i,galPos));
                galPos = line.find('#', galPos + 1);
            }
            i++;
        }
    }

    int shiftCount = 0;
    int origRowLen = space[0].length();
    //expand any columns
    for (int j = 0; j < space[0].length(); j++)
    {
        bool allSpace = true;
        for (int i = 0; i < space.size(); i++)
        {
            allSpace = allSpace && space[i][j] == '.';
        }
        if(allSpace) emptySpaceCols.insert(j);
    }

    int result1 = 0;
    unsigned long long result2 = 0;
    const unsigned long long EXPANSION_MULTIPLIER = 1000000;

    for(int i = 0; i < galaxies.size()-1; i++)
    {
        for(int j = i+1; j < galaxies.size(); j++)
        {
            int len = abs(galaxies[j].second - galaxies[i].second) + abs(galaxies[j].first - galaxies[i].first);
            result1 += len;
            result2 += (unsigned)len;

            //are there empty col's inbetween?
            int colSign = copysign(1, galaxies[j].second - galaxies[i].second);
            for(int jIt = galaxies[i].second; jIt != galaxies[j].second; jIt += colSign)
            {
                if(emptySpaceCols.count(jIt) == 1)
                {
                     result1 += 1;
                     result2 += EXPANSION_MULTIPLIER - 1;
                }
            }

            int rowSign = copysign(1, galaxies[j].first - galaxies[i].first);
            for(int iIt = galaxies[i].first; iIt != galaxies[j].first; iIt += rowSign)
            {
                if(emptySpaceRows.count(iIt) == 1)
                {
                     result1 += 1;
                     result2 += EXPANSION_MULTIPLIER - 1;
                }
            }
        }
    }
    std::cout << "Solved ten: " << result1 << ":" << result2 << std::endl;
    output << result1 << std::endl;
    output << result2 << std::endl;
}
