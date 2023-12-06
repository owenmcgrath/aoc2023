#include "loadInput.h"

void LoadInput::load(const string& file, vector<string>& input)
{
    ifstream inHandle(file);
    string line;
    if(inHandle.is_open())
    {
        while(getline(inHandle, line)) input.push_back(line);
    }
}