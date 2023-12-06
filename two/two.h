/*
int arr[3] for each set

vector<vector<int>>

*/

#ifndef TWO_H
#define TWO_H

using namespace std;

#include <string>
#include <vector>
#include <unordered_map>
#include "../lib/trie.h"
#include "ctype.h"
#include "one.h"

class two
{
public:
    two(){}

    static void parseGame(string game, vector<vector<int>>& sets);
    static bool gamePossible(const vector<vector<int>>& sets);
    static int calcPower(const vector<vector<int>>& sets);

    static void solve();


};

#endif