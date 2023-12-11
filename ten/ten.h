#ifndef TEN_H
#define TEN_H

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <fstream>
#include  "../lib/loadInput.h"


using namespace std;

class ten 
{
public:

    enum Dir
    {
        North,
        South,
        East,
        West
    };

    static void solve();
    static int findLoop(vector<string>& tiles, vector<pair<int, int>>& loopCoords);
    static void nextLoopLink(const vector<string>& tiles, int& i, int& j, Dir& dir);
    static int countInsides(const vector<string>& tiles, const vector<pair<int,int>>& loopCoords);

};

#endif