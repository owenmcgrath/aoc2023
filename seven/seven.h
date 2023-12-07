#ifndef SEVEN_H
#define SEVEN_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include "ctype.h"
#include "map"
#include "unordered_map"


using namespace std;

class seven 
{
public:

    static void solve();

    static void parseHand(const string& handAndBid, unordered_map<char,int>& hand, int& bid);
    static void insertHand(const unordered_map<char,int>& hand, const string& handStr, int bid, vector<multimap<string, int>>& ranks, bool joker=false);
    static unsigned long calculateWinnings(const vector<multimap<string,int>>& ranks);
};

#endif