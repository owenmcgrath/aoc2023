#ifndef FOURTEEN_H
#define FOURTEEN_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include <unordered_set>
#include <unordered_map>


using namespace std;

class fourteen 
{
public:

    static void solve();

    static unsigned long getTotalLoadNorth(const vector<string>& rocks);
    static unsigned long getTotalLoad(const vector<string>& rocks);

    static void spinCycle(vector<string>& rocks, int numCycles);

    static size_t rocksHash(const vector<string>& rocks);
};

#endif