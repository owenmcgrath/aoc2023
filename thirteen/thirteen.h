#ifndef THIRTEEN_H
#define THIRTEEN_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include <unordered_set>
#include <unordered_map>


using namespace std;

class thirteen 
{
public:

    static void solve();

    static vector<int> findVerticalLineOfReflection(const vector<string>& mirrorValley, int startRow, int endRow);
    static vector<int> findHorizontalLineOfReflection(const vector<string>& mirrorValley, int startRow, int endRow);
    static bool compareColumn(const vector<string>& mirrorValley, int startRow, int endRow, int col1, int col2);

};

#endif