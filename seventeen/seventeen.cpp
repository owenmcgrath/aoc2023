#include "seventeen.h"

void seventeen::solve()
{
    const string INPUT_FILE = "../input/16.txt";
    const string OUTPUT_FILE = "../output/16.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    int result1 = 0; 
    int result2 = 0;

    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved seventeen " << result1 << ":" << result2 << endl;
}

int seventeen::leastHeatLoss(const vector<string>& cityBlocks)
{
    vector<vector<int>> distances(cityBlocks.size(), vector<int>(cityBlocks[0].length(), INT32_MAX));
    vector<vector<int>> prev(cityBlocks.size(), vector<int>(cityBlocks[0].length(), -1));
    distances[0][0] = 0; 
    map<int, pair<int,int>> q;
    pair<int,int> end = {cityBlocks.size() - 1, cityBlocks[0].length() - 1};
    q[0] = make_pair(0,0);

    while(!q.empty())
    {
        pair<int,int> where = q.begin()->second;
        if(where == end) return distances[where.first][where.second];
        q.erase(q.begin());
        
        //left
        if(distances[where.first - 1][where.second] > (distances[where.first][where.second]))
        {
            q.erase(distances[where.first-1][where.second]);
        }
    }
    return 0;
}
