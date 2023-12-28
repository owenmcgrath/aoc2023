#ifndef EIGHTEEN_H
#define EIGHTEEN_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include <vector>
#include <cstdlib>


using namespace std;

typedef vector<pair<long,long>> Trench;

class eighteen 
{
public:

    static void solve();
    static unsigned long buildTrench(const vector<string>& instructions, Trench& t, bool part2 = false);
    static unsigned long trenchArea(const Trench& t);



};

#endif