#include "thirteen.h"

void thirteen::solve()
{
    const string INPUT_FILE = "../input/13.txt";
    const string OUTPUT_FILE = "../output/13.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    int startRow = 0;
    int endRow = 0;
    int result1 = 0;

    while (endRow < input.size())
    {
        while (endRow < input.size() && input[endRow] != "")
        {
            endRow++;
        }

        auto horiz = findHorizontalLineOfReflection(input, startRow, endRow-1);
        auto vert = findVerticalLineOfReflection(input, startRow, endRow-1);
        for (int row : horiz)
            result1 += 100 * row;
        for (int col : vert)
            result1 += col;

        startRow = endRow+1;
        endRow++;
    }

    ofstream output(OUTPUT_FILE);
    int result2 = 0;
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved thirteen " << result1 << ":" << result2 << endl;
}
vector<int> thirteen::findVerticalLineOfReflection(const vector<string> &mirrorValley, int startRow, int endRow)
{
    int colToCheck = 0;
    vector<int> reflections;
    while (colToCheck < mirrorValley[startRow].length() - 1)
    {
        int lCol = colToCheck;
        int rCol = colToCheck + 1;
        while (lCol >= 0 && rCol < mirrorValley[startRow].length() && compareColumn(mirrorValley, startRow, endRow, lCol, rCol))
        {
            lCol--;
            rCol++;
        }
        if (rCol - lCol > 3 && (lCol < 0 || rCol >= mirrorValley[startRow].length()))
            {reflections.push_back(1+((lCol + rCol) / 2)); return reflections;}
        colToCheck = rCol;
    }

    return reflections;
}

vector<int> thirteen::findHorizontalLineOfReflection(const vector<string> &mirrorValley, int startRow, int endRow)
{
    vector<int> reflections;
    int rowToCheck = startRow;
    while (rowToCheck < endRow - 1)
    {
        int upRow = rowToCheck;
        int downRow = rowToCheck + 1;
        while (upRow >= startRow && downRow <= endRow && mirrorValley[upRow] == mirrorValley[downRow])
        {
            upRow--;
            downRow++;
        }
        if (downRow - upRow > 3 && (downRow > endRow || upRow < startRow))
            {reflections.push_back(1+((downRow + upRow) / 2) - startRow); return reflections; }
        rowToCheck = downRow;
    }
    return reflections;
}

bool thirteen::compareColumn(const vector<string> &mirrorValley, int startRow, int endRow, int col1, int col2)
{
    bool equal = true;
    for (int i = startRow; i <= endRow; i++)
    {
        equal = equal && mirrorValley[i][col1] == mirrorValley[i][col2];
    }
    return equal;
}

//300
//6
//4
//400