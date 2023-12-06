#ifndef SIX_H
#define SIX_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>


using namespace std;

class six 
{
public:

    static void solve();

    static void parseTimes(const string& timeStr, vector<pair< long long, long long>>& races);
    static void parseDistances(const string& distStr, vector<pair< long long, long long>>& races);

    static  long long getNumWaysToBeatRecord(const vector<pair< long long, long long>>& races);

};

#endif