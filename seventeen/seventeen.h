#ifndef SEVENTEEN_H
#define SEVENTEEN_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include <map>


using namespace std;

class seventeen 
{
public:

    enum Direction {North, South, East, West};
    void solve();
    int leastHeatLoss(const vector<string>& cityBlocks);


};

#endif

/*
need 2 2d arrays representing vertices and prev.

vector<int> dist; sizeof m*n to INT_MAX
vector<int> prev; sizeof m*n to -1
map<int, dist> prioQ; insert all the values
dist[0] = 0;


for auto u : prioQ







*/