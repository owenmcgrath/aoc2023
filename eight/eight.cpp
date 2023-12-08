#include "eight.h"
#include "numeric"

void eight::solve()
{
    ifstream input("../input/8.txt");
    ofstream output("../output/8.txt");

    unordered_map<string, pair<string, string>> network;
    string directions;
    getline(input, directions);
    string next;
    getline(input, next);
    string line;
    while (getline(input, line))
    {
        network[line.substr(0, 3)] = pair<string, string>(line.substr(7, 3), line.substr(12, 3));
    }

    int result1 = stepsToZzz(directions, network);
    unsigned long long result2 = simulStepsToZzz(directions, network);

    std::cout << "Solved eight: " << result1 << ":" << result2 << std::endl;
    output << result1 << std::endl;
    output << result2 << std::endl;
}

int eight::stepsToZzz(const string &directions, const unordered_map<string, pair<string, string>> &network)
{
    bool foundZzz = false;
    int count;
    string currNode = "AAA";
    int counter = 0;
    while (!foundZzz)
    {
        for (char c : directions)
        {
            counter++;
            currNode = c == 'R' ? network.at(currNode).second : network.at(currNode).first;
            if (currNode == "ZZZ")
            {
                foundZzz = true;
                return counter;
            }
        }
    }
    return counter;
}

unsigned long long eight::simulStepsToZzz(const string &directions, const unordered_map<string, pair<string, string>> &network)
{

    unsigned long long result = 0;
    for (auto &node : network)
    {

        if (node.first[2] == 'A')
        {
            bool foundZ = false;
            string currNode = node.first;
            unsigned long long counter = 0;
            while (!foundZ)
            {
                for (char c : directions)
                {
                    counter++;
                    currNode = c == 'R' ? network.at(currNode).second : network.at(currNode).first;
                    if (currNode[2] == 'Z')
                    {
                        foundZ = true;
                        if(result == 0) result = counter;
                        else result = lcm(result,counter);
                        break;
                    }
                }
            }
        }
    }
    return result;
}