#include "three.h"

void three::solve()
{
    const string INPUT_FILE = "../input/3.txt";
    const string OUTPUT_FILE = "../output/3.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    int result1 = sumPartNums(input);

    int result2 = sumGearRatios(input);

    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved three " << result1 << ":" << result2 << endl;
}

bool three::isSymbol(char c)
{
    return !(isdigit(c) || c == '.');
}

bool three::checkAdjacentForSymbol(const vector<string> &input, int row, int col)
{
    bool checkLeft = col > 0 && !isdigit(input[row][col - 1]);
    bool checkRight = col < input[0].length() - 1 && !isdigit(input[row][col + 1]);
    bool checkUp = row > 0;
    bool checkDown = row < input.size() - 1;

    bool foundSymbol = false;
    if (checkLeft)
    {
        foundSymbol = foundSymbol || isSymbol(input[row][col - 1]);
        if (checkUp)
            foundSymbol = foundSymbol || isSymbol(input[row - 1][col - 1]);
        if (checkDown)
            foundSymbol = foundSymbol || isSymbol(input[row + 1][col - 1]);
    }

    if (checkRight)
    {
        foundSymbol = foundSymbol || isSymbol(input[row][col + 1]);
        if (checkUp)
            foundSymbol = foundSymbol || isSymbol(input[row - 1][col + 1]);
        if (checkDown)
            foundSymbol = foundSymbol || isSymbol(input[row + 1][col + 1]);
    }

    if (checkUp)
        foundSymbol = foundSymbol || isSymbol(input[row - 1][col]);
    if (checkDown)
        foundSymbol = foundSymbol || isSymbol(input[row + 1][col]);

    return foundSymbol;
}

int three::getGearRatio(const vector<string> &input, int row, int col)
{
    bool checkLeft = col > 0;
    bool checkRight = col < input[0].length() - 1;
    bool checkUp = row > 0;
    bool checkDown = row < input.size() - 1;
    int count = 0;
    int ratio = 1;

    if (checkUp)
    {
        int up = getValue(input, row - 1, col);
        if (up != 0)
        {
            count++;
            ratio *= up;
        }
        else
        {
            // check both upper corners
            int upright = 1;
            int upleft = 1;
            if (checkRight)
                upright = getValue(input, row - 1, col + 1);
            if (checkLeft)
                upleft = getValue(input, row - 1, col - 1);
            if (upleft != 0)
            {
                ratio *= upleft;
                count++;
            }
            if (upright != 0) 
            {
                ratio *= upright;
                count++;
            }
        }
    }

    if (row + 1 < input.size())
    {
        int down = getValue(input, row + 1, col);
        if (down != 0)
        {
            count++;
            ratio *= down;
        }
        else
        {
            // check both lower corners
            int downleft = 1;
            int downright = 1;
            if (checkRight)
                downright = getValue(input, row + 1, col + 1);
            if (checkLeft)
                downleft = getValue(input, row + 1, col - 1);

            if (downleft != 0)
            {
                ratio *= downleft;
                count++;
            }
            if (downright != 0)
            {
                ratio *= downright;
                count++;
            }
        }
    }

    if (checkLeft)
    {
        int left = getValue(input, row, col - 1);
        if (left != 0)
        {
            ratio *= left;
            count++;
        }
    }
    if (checkRight)
    {
        int right = getValue(input, row, col + 1);
        if (right != 0)
        {
            ratio *= right;
            count++;
        }
    }

    std::cout << count << " " << row << "," << col << " " << ratio << std::endl;

    return count >= 2 ? ratio : 0;
}

int three::sumPartNums(const vector<string> &input)
{
    int curNum = -1;
    int sum = 0;
    bool hasAdjacentSymbol = false;
    for (int row = 0; row < input.size(); row++)
    {
        for (int col = 0; col < input[row].length(); col++)
        {
            if (isdigit(input[row][col]))
            {
                hasAdjacentSymbol = hasAdjacentSymbol || checkAdjacentForSymbol(input, row, col);
                int val = input[row][col] - '0';
                curNum = curNum == -1 ? val : (10 * curNum) + val;
            }
            else
            {
                if (hasAdjacentSymbol)
                    sum += curNum;
                curNum = -1;
                hasAdjacentSymbol = false;
            }
        }
        if (curNum != -1)
        {
            if (hasAdjacentSymbol)
                sum += curNum;
            hasAdjacentSymbol = false;
            curNum = -1;
        }
    }
    return sum;
}

int three::sumGearRatios(const vector<string> &input)
{
    int sum = 0;
    for (int row = 0; row < input.size(); row++)
    {
        for (int col = 0; col < input[row].length(); col++)
        {
            if (input[row][col] == '*')
                sum += getGearRatio(input, row, col);
        }
    }
    return sum;
}

int three::getValue(const vector<string> &input, int row, int col)
{
    const string rowStr = input[row];
    int start = col;
    int end = col;
    while (start >= 0 && isdigit(rowStr[start]))
    {
        start--;
    }

    while (end < rowStr.length() && isdigit(rowStr[end]))
    {
        end++;
    }

    int val = 0;
    if (end > start)
    {
        for (int i = start+1; i < end; i++)
        {
            val *= 10;
            val += (rowStr[i] - '0');
        }
    }
    else if(isdigit(rowStr[col])) 
    {
        val = rowStr[col] - '0';
    }

    return val;
}