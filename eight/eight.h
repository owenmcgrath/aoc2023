#ifndef EIGHT_H
#define EIGHT_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include "ctype.h"
#include "map"
#include "unordered_map"
#include "set"


using namespace std;

class eight 
{
public:

    static void solve();

    static void parseMap(const string& mapStr, unordered_map<string,pair<string,string>>& network);
    static int stepsToZzz(const string& directions, const unordered_map<string, pair<string,string>>& network);
    static unsigned long long simulStepsToZzz(const string& directions, const unordered_map<string, pair<string,string>>& network);

};

#endif