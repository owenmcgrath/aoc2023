#include "sixteen.h"

void sixteen::solve()
{
    const string INPUT_FILE = "../input/16.txt";
    const string OUTPUT_FILE = "../output/16.txt";

    Contraption input;
    LoadInput::load(INPUT_FILE, input);

    TilesEnergized te;
    projectBeam(input, te, East, 0, 0, false);
    int result1 = te.size();
    int result2 = 0;

    for(int i = 0; i < input.size(); i++)
    {
        TilesEnergized teRight;
        projectBeam(input, teRight, East, i, 0, false);
        result2 = max(result2, (int)teRight.size());

        TilesEnergized teLeft;
        projectBeam(input, teLeft, West, i, input[0].length() - 1, false);
        result2 = max(result2, (int) teLeft.size());
    }

    for(int j = 0; j < input[0].length(); j++)
    {
        TilesEnergized teUp;
        projectBeam(input, teUp, North, input.size() - 1, j, false);
        result2 = max(result2, (int) teUp.size());


        TilesEnergized teDown;
        projectBeam(input, teDown, South, 0, j, false);
        result2 = max(result2, (int) teDown.size());
    }


    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved sixteen " << result1 << ":" << result2 << endl;
}

// assuming (more like praying) there isnt any cycles because this would infinite loop otherwise.
void sixteen::projectBeam(const Contraption &contraption, TilesEnergized &energized, Direction dir, int i, int j, bool lastEnergized)
{
    if (i < 0 || i >= contraption.size() || j < 0 || j >= contraption[0].size())
        return;

    int idx = i * contraption[0].length() + j;

    // if we traverse two previously traversed simultaneously then we are cycling.
    bool isEnergized = energized.count(idx) && energized[idx].count(dir);
    //cout << i << "," << j << " " << lastEnergized << " " << isEnergized << endl;
    if (lastEnergized && isEnergized)
    {
        return;
    }

    energized[idx].insert(dir);
    char material = contraption[i][j];

    // split east-west
    if (material == '-' && (dir == North || dir == South))
    {
        int leftCount = 0;
        int rightCount = 0;
        projectBeam(contraption, energized, West, i, j - 1, isEnergized);
        projectBeam(contraption, energized, East, i, j + 1, isEnergized);
    }
    // split north-south
    else if (material == '|' && (dir == East || dir == West))
    {
        int upCount = 0;
        int downCount = 0;
        projectBeam(contraption, energized, North, i - 1, j, isEnergized);
        projectBeam(contraption, energized, South, i + 1, j, isEnergized);
    }
    else
    {

        // traverse a single beam!
        switch (dir)
        {
        case North:

            if (material == '.' || material == '|')
            {
                projectBeam(contraption, energized, dir, i - 1, j, isEnergized);
            }
            else if (material == '\\')
            {
                projectBeam(contraption, energized, West, i, j - 1, isEnergized);
            }
            else if (material == '/')
            {
                projectBeam(contraption, energized, East, i, j + 1, isEnergized);
            }
            break;
        case South:
            if (material == '.' || material == '|')
            {
                projectBeam(contraption, energized, dir, i + 1, j, isEnergized);
            }
            else if (material == '\\')
            {
                projectBeam(contraption, energized, East, i, j + 1, isEnergized);
            }
            else if (material == '/')
            {
                projectBeam(contraption, energized, West, i, j - 1, isEnergized);
            }
            break;
        case East:
            if (material == '.' || material == '-')
            {
                projectBeam(contraption, energized, dir, i, j + 1, isEnergized);
            }
            else if (material == '\\')
            {
                projectBeam(contraption, energized, South, i + 1, j, isEnergized);
            }
            else if (material == '/')
            {
                projectBeam(contraption, energized, North, i - 1, j, isEnergized);
            }
            break;
        case West:
            if (material == '.' || material == '-')
            {
                projectBeam(contraption, energized, dir, i, j - 1, isEnergized);
            }
            else if (material == '\\')
            {
                projectBeam(contraption, energized, North, i - 1, j, isEnergized);
            }
            else if (material == '/')
            {
                projectBeam(contraption, energized, South, i + 1, j, isEnergized);
            }
            break;
        }
    }
}