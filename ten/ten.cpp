#include "ten.h"

void ten::solve()
{

    // get i/o file handles
    ofstream output("../output/10.txt");

    vector<string> tiles;
    vector<pair<int, int>> loop;
    LoadInput::load("../input/10.txt", tiles);

    int result1 = findLoop(tiles, loop);
    int result2 = countInsides(tiles, loop);

    std::cout << "Solved ten: " << result1 << ":" << result2 << std::endl;
    output << result1 << std::endl;
    output << result2 << std::endl;
}

int ten::findLoop(vector<string> &tiles, vector<pair<int, int>> &loopCoords)
{
    // find S.
    int i, j;
    bool foundS = false;
    for (i = 0; i < tiles.size() && !foundS; i++)
    {
        for (j = 0; j < tiles[i].size() && !foundS; j++)
        {
            if (tiles[i][j] == 'S')
                foundS = true;
        }
    }
    i--;
    j--;

    int sI = i;
    int sJ = j;

    // traverse
    Dir dir;
    // check if tiles[i-1][j]
    if (i - 1 >= 0 && (tiles[i - 1][j] == '|' || tiles[i - 1][j] == 'F' || tiles[i - 1][j] == '7'))
    {
        dir = North;
        i--;
    }
    else if (j - 1 >= 0 && (tiles[i][j - 1] == 'F' || tiles[i][j - 1] == 'L' || tiles[i][j - 1] == '-'))
    {

        dir = West;
        j--;
    }

    else if (j + 1 >= 0 && (tiles[i][j + 1] == '7' || tiles[i][j + 1] == 'J' || tiles[i][j + 1] == '-'))

    {
        dir = East;
        j++;
    }

    if (i + 1 >= 0 && (tiles[i + 1][j] == '|' || tiles[i + 1][j] == 'L' || tiles[i + 1][j] == 'J'))

    {
        dir = South;
        i++;
    }

    Dir startDir = dir;

    int count = 1;
    Dir prevDir;
    tiles[sI][sJ] = '|';

    if(tiles[i][j] != '-' && tiles[i][j] != '|') loopCoords.push_back(make_pair(i,j));


    while (!(i == sI && j == sJ))
    {
        nextLoopLink(tiles, i, j, dir);
        if(tiles[i][j] != '-' && tiles[i][j] != '|') loopCoords.push_back(make_pair(i,j));
        count++;
    }


    return count / 2;
}

void ten::nextLoopLink(const vector<string> &tiles, int &i, int &j, Dir &dir)
{
    char tile = tiles[i][j];
    switch (dir)
    {
    case North:
        switch (tile)
        {
        case 'F':
            dir = East;
            break;
        case '7':
            dir = West;
            break;
        case '|':
            dir = North;
            break;
        }
        break;
    case South:
        switch (tile)
        {
        case 'L':
            dir = East;
            break;
        case 'J':
            dir = West;
            break;
        case '|':
            dir = South;
            break;
        }
        break;
    case East:
        switch (tile)
        {
        case '7':
            dir = South;
            break;
        case 'J':
            dir = North;
            break;
        case '-':
            dir = East;
            break;
        }
        break;
    case West:
        switch (tile)
        {
        case 'F':
            dir = South;
            break;
        case 'L':
            dir = North;
            break;
        case '-':
            dir = West;
            break;
        }
        break;
    default:
        break;
    }

    switch (dir)
    {
    case North:
        i--;
        return;
    case South:
        i++;
        return;
    case East:
        j++;
        return;
    case West:
        j--;
        return;
    }
}

bool pnpoly(const std::vector<pair<int,int>>& verts, int testx, int testy){
    int num = (int)verts.size();
    int j = num - 1;
    bool ret = false;
    for(int i=0; i<num; ++i){
        if(testx == verts[i].first && testy == verts[i].second){
            return true;
        }

        if((verts[i].second > testy) != (verts[j].second > testy)) {
            int slope = (testx - verts[i].first) * (verts[j].second - verts[i].second) - (verts[j].first - verts[i].first) * (testy - verts[i].second);
            if(slope == 0){
                return true;
            }
            if ((slope < 0) != (verts[j].second < verts[i].second)){
                ret = !ret;
            }
        }
        j = i;
    }

    return ret;
}

int ten::countInsides(const vector<string> &tiles, const vector<pair<int,int>> &loopCoords)
{
    int count = 0;
    for (int i = 0; i < tiles.size(); i++)
    {
        for(int j = 0; j < tiles[i].size(); j++)
        {
            if(pnpoly(loopCoords, i,j)) count++;
        }
    }
    return count;
}