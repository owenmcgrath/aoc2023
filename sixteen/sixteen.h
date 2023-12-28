#ifndef SIXTEEN_H
#define SIXTEEN_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include <unordered_set>
#include <unordered_map>


using namespace std;

typedef vector<string> Contraption;

class sixteen 
{
public:

    enum Direction {North, South, East, West};
    typedef unordered_map<int, unordered_set<Direction>> TilesEnergized;
    static void solve();
    static void projectBeam(const Contraption& contraption, TilesEnergized& energized, Direction dir, int i, int j, bool lastEnergized);
};

#endif