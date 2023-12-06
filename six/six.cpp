#include "six.h"


void six::solve()
{
    const string INPUT_FILE = "../input/6.txt";
    const string OUTPUT_FILE = "../output/6.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    vector<pair<long long,long long>> races;
    parseTimes(input[0], races);
    parseDistances(input[1], races);

    int result1 = getNumWaysToBeatRecord(races);


    string combinedTime;
    string combinedDistance;
    for(auto& race : races)
    {
        combinedTime += to_string(race.first);
        combinedDistance += to_string(race.second);
    }

    
    vector<pair<long long, long long>> combinedRace = {{stoul(combinedTime), stoul(combinedDistance)}};
    int result2 = getNumWaysToBeatRecord(combinedRace);

    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved six " << result1 << ":" << result2 << endl;

}

void six::parseTimes(const string& timeStr, vector<pair<long long,long long>>& races)
{
    int idx = timeStr.find(":") + 1;
    while(idx < timeStr.length())
    {
        while(timeStr[idx] == ' ')idx++;
        long long val = 0;
        while(idx < timeStr.length() && timeStr[idx] != ' ')
        {
            val *= 10;
            val += timeStr[idx++] - '0';
        }
        races.emplace_back(pair<long long,long long>(val,0));
    }
}


void six::parseDistances(const string& distStr, vector<pair<long long,long long>>& races)
{
    int idx = distStr.find(":") + 1;
    int ctr = 0;
    while(idx < distStr.length())
    {
        while(distStr[idx] == ' ')idx++;
        long long val = 0;
        while(idx < distStr.length() && distStr[idx] != ' ')
        {
            val *= 10;
            val += distStr[idx++] - '0';
        }
        races[ctr++].second = val;
    }
}


long long six::getNumWaysToBeatRecord(const vector<pair<long long,long long>>& races)
{
    //y= -x^2 + time*x 
    //need range of value for y >= dist
    //y = -x^2 + time*x - dist;
    // x = -time + (sqrt(time*time + 4*dist)/-2)
    // x = -time - (sqrt(time*time + 4*dist)/-2)
    long long retVal = 1;
    for(auto& td : races)
    {
        double root = sqrt((td.first*td.first) - (4*td.second));
        double high = ((-td.first) - root)/-2;
        double low = ((-td.first) + root)/-2;

        long long lowHoldTime = ((long long)low) + 1;
        long long highHoldTime = (fmod(high, 1.0) > 0) ? (long long)high : (long long)(high - 1);
        retVal *= (highHoldTime - lowHoldTime + 1);

    }

    return retVal;
}