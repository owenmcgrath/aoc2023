#include "two.h"

void two::parseGame(string game, vector<vector<int>>& sets)
{
    //get the colon
    size_t idx = game.find(':') + 2;

    sets.push_back(vector<int>(3,0));
    while(idx < game.length())
    {
        int count = 0;
        while(isdigit(game[idx]))
        {
            count *= 10;
            count += (game[idx] - '0');
            idx++;
        }
        idx++;
        switch(game[idx])
        {
            case 'r':
                sets.back()[0] = count;
                break;
            case 'g':
                sets.back()[1] = count;
                break;
            case 'b':
                sets.back()[2] = count;
                break;
            default:
                std::cout << "parse game broke sum ting wong" << std::endl;
                return;
        }

        while(idx < game.length())
        {
            if(game[idx] ==';') 
            {
                sets.push_back(vector<int>(3,0));
                break;
            }
            if(game[idx] ==',') break;
            idx++;
        }
        idx+= 2;
    }
}

bool two::gamePossible(const vector<vector<int>>& sets)
{
    bool possible = true;
    for(auto& set : sets)
    {
        possible = possible && set[0] <= 12;
        possible = possible && set[1] <= 13;
        possible = possible && set[2] <= 14;
    }
    return possible;
}

int two::calcPower(const vector<vector<int>>& sets)
{
    int maxR = 0, maxG = 0, maxB = 0;

    for(auto& set : sets)
    {
        maxR = max(set[0], maxR);
        maxG = max(set[1], maxG);
        maxB = max(set[2], maxB);
    }
    return (maxR * maxG * maxB);
}

void two::solve()
{
    string line;
    ifstream input("../input/2.txt");
    ofstream output("../output/2.txt");

    int sum1 = 0;
    int sum2 = 0;
    int ctr = 1;

    if(input.is_open())
    {
        while(getline(input, line))
        {
            vector<vector<int>> sets;
            parseGame(line, sets);
            bool result = gamePossible(sets);
            int result2 = calcPower(sets);
            if(result) sum1+= ctr;
            sum2 += result2;
            std::cout << line << " " << result << ":" << result2 <<  std::endl;
            ctr++;
        }

        std::cout << "Solved two: " << sum1 << ":" <<  sum2 << std::endl;
        output << sum1 << std::endl;
        output << sum2 << std::endl;


        input.close();
        output.close();
    }
}
