#ifndef FIFTEEN_H
#define FIFTEEN_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <cassert>
#include <string>
#include <utility>

using namespace std;

typedef pair<string,int> Lens;
typedef list<Lens> Box;
typedef unordered_map<unsigned int, Box> Boxes;
typedef unordered_map<string, Box::iterator> LensMap;


class fifteen 
{
public:

    static void solve();
    static unsigned int getHash(const string& line, int startIdx, int endIdx);
    static void operateOnBoxes(Boxes& boxes, LensMap& lm, string op);

};

#endif