#ifndef NINE_H
#define NINE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>


using namespace std;

class nine 
{
public:

    static void solve();

    static long long predictReading(vector<long long>& values);
    static long long predictHistory(vector<long long>& values);
};

#endif