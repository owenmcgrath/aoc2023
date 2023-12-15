#include "fifteen.h"

void fifteen::solve()
{

    // get i/o file handles
    ofstream output("../output/15.txt");
    ifstream inHandle("../input/15.txt");
    string initSequence;
    if (inHandle.is_open())
    {
        getline(inHandle, initSequence);
    }

    int lowIdx = 0;
    int highIdx = 0;
    int result1 = 0;
    int result2 = 0;

    //part 1 test case
    string test("HASH");
    assert(getHash(test, 0, 3) == 52);

    Boxes boxes;
    LensMap lm;

    while (lowIdx < initSequence.size())
    {
        highIdx = initSequence.find(',', lowIdx);
        if(highIdx == -1) highIdx = initSequence.size();
        result1 += getHash(initSequence, lowIdx, highIdx - 1);
        operateOnBoxes(boxes, lm, initSequence.substr(lowIdx, highIdx - lowIdx));

        lowIdx = highIdx + 1;
    }

    // score boxes
    for(auto b : boxes)
    {
        int count = 1;
        for(auto l = b.second.begin();  l != b.second.end(); l++)
        {
            result2 += (1 + b.first) * count++ * (*l).second;
        }
    }

    std::cout << "Solved fifteen: " << result1 << ":" << result2 << std::endl;
    output << result1 << std::endl;
    output << result2 << std::endl;
}

unsigned int fifteen::getHash(const string &line, int startIdx, int endIdx)
{
    unsigned int retVal = 0;
    for (int i = startIdx; i <= endIdx; i++)
    {
        retVal += (unsigned char)line[i];
        retVal *= 17;
        retVal = retVal % 256;
    }
    return retVal;
}

void fifteen::operateOnBoxes(Boxes &boxes, LensMap &lm, string op)
{
    char opChar = ' ';
    int opIdx = 0;

    //get the index of the operation and the operation itself
    for (int i = 0; i < op.length(); i++)
    {
        if (op[i] == '=' || op[i] == '-')
        {
            opIdx = i;
            opChar = op[i];
        }
    }

    //get the box ID
    unsigned int boxId = getHash(op, 0, opIdx - 1);
    
    //get the operation ID
    string newOp = op.substr(0, opIdx);

    //we are inserting/replacing a lens
    if (opChar == '=')
    {
        //if we need to replace, replace
        if (lm.count(newOp) > 0)
        {
            (*lm[newOp]).second = op.back() - '0';
        }

        //otherwise insert
        else
        {
            boxes[boxId].push_back(make_pair(newOp, op.back() - '0'));
            
            //store a reference to the list node, makes it quicker to erase
            lm[newOp] = boxes[boxId].end();
            lm[newOp]--;
        }
    }

    //we are deleting a lens
    else if (lm.count(newOp))
    {
        boxes[boxId].erase(lm[newOp]);
        lm.erase(newOp);

        //no need to erase the box, it will get ignored come time to score if its empty
    }
}