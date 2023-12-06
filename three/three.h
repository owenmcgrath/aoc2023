#ifndef THREE_H
#define THREE_H

#include "../lib/loadInput.h"
#include "ctype.h"
#include <iostream>

class three 
{
public:

    static void solve();
    static bool checkAdjacentForSymbol(const vector<string>& input, int row, int col);
    static int sumPartNums(const vector<string>& input);
    static bool isSymbol(char c);
    static int sumGearRatios(const vector<string>& input);
    static int getGearRatio(const vector<string>& input, int row, int col);
    static int getValue(const vector<string>& input, int row, int col);

};


#endif