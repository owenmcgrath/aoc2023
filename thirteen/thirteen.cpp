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

        auto horiz = findHorizontalLineOfReflection(input, startRow, endRow - 1);
        auto vert = findVerticalLineOfReflection(input, startRow, endRow - 1);
        result1 += 100 * horiz;
        result1 += vert;

        startRow = endRow + 1;
        endRow++;
    }

    ofstream output(OUTPUT_FILE);
    int result2 = 0;
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved thirteen " << result1 << ":" << result2 << endl;
}
int thirteen::findVerticalLineOfReflection(const vector<string> &mirrorValley, int startRow, int endRow)
{
    int colToCheck = 0;
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
        {
            return 1 + ((lCol + rCol) / 2);
        }
        colToCheck = rCol;
    }

    return 0;
}

int thirteen::findHorizontalLineOfReflection(const vector<string> &mirrorValley, int startRow, int endRow)
{
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
        {
            return (1 + ((downRow + upRow) / 2) - startRow);
        }
        rowToCheck = downRow;
    }
    return 0;
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

// 300
// 6
// 4
// 400