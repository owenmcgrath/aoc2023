#ifndef FOUR_H
#define FOUR_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include "../lib/loadInput.h"
#include "ctype.h"

using namespace std;

class four 
{
public:

    static void solve();

    static void parseCard(const string& card, unordered_set<int>& winners, vector<int>& numbers);

    static int calculateScore(const unordered_set<int>& winners, vector<int>& numbers);

    static int numWinners(const unordered_set<int>& winners, vector<int>& numbers);

};


#endif