#include "eighteen.h"

void eighteen::solve()
{
    const string INPUT_FILE = "../input/18.txt";
    const string OUTPUT_FILE = "../output/18.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    Trench t;
    int b = buildTrench(input, t);
    int a = trenchArea(t);
    int i = a - (b / 2) + 1;
    int result1 = i + b;


    Trench t2;
    unsigned long b2 = buildTrench(input, t2, true);
    unsigned long a2 = trenchArea(t2);
    unsigned long i2 = a2 - (b2/2) + 1;
    unsigned long result2 = i2 + b2;

    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved eighteen " << result1 << ":" << result2 << endl;
}

unsigned long eighteen::buildTrench(const vector<string> &instructions, Trench &t, bool part2)
{
    long x = 0;
    long y = 0;
    unsigned long b = 0;

    for (int i = 0; i < instructions.size(); i++)
    {
        string instruction = instructions[i];
        char dir;
        unsigned long len = 0;

        if (part2)
        {
            char dirVal = instruction[instruction.length() - 2];
            if(dirVal == '0') dir = 'R';
            else if(dirVal == '1') dir = 'D';
            else if(dirVal == '2') dir = 'L';
            else if(dirVal == '3') dir = 'U';

            string lenStr = instruction.substr(instruction.length() - 7, 5);
            char* p;
            len = strtol(lenStr.c_str(), &p, 16);
        }
        else
        {
            dir = instruction[0];
            int lenIdx = 2;

            while (instruction[lenIdx] != ' ')
            {
                len *= 10;
                len += instruction[lenIdx++] - '0';
            }
        }

        b += len;

        switch (dir)
        {
        case 'L':
            t.push_back(make_pair(x - len, y));
            x = x - len;
            break;
        case 'R':
            t.push_back(make_pair(x + len, y));
            x = x + len;
            break;
        case 'D':
            t.push_back(make_pair(x, y - len));
            y = y - len;
            break;
        case 'U':
            t.push_back(make_pair(x, y + len));
            y = y + len;
            break;
        }
    }
    return b;
}

unsigned long eighteen::trenchArea(const Trench &t)
{
    long sum = 0;
    for (int i = t.size() - 1; i > 0; i--)
    {
        sum += (t[i].first * t[i - 1].second) - (t[i - 1].first * t[i].second);
    }

    sum += (t.front().first * t.back().second) - (t.back().first * t.front().second);
    return abs(sum / 2);
}
