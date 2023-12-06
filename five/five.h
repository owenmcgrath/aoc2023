#ifndef FIVE_H
#define FIVE_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include "../lib/loadInput.h"
#include "ctype.h"
#include <algorithm>
#include <thread>

using namespace std;

class five 
{
public:

    static void solve();

    static void parseSeeds(const string& seedStr, vector<unsigned long>& seeds);
    static void parseMap(const vector<string>& input, vector<vector<vector<unsigned long>>>& maps);
    static unsigned long getLocation(const vector<vector<vector<unsigned long>>>& maps, unsigned long seed);
    static void getLocRange(const vector<vector<vector<unsigned long>>>& maps, unsigned long seed, unsigned long range);
};


#endif