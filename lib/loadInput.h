#ifndef LOAD_INPUT_H
#define LOAD_INPUT_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class LoadInput
{
public:
    static void load(const string& file, vector<string>& input);
};

#endif