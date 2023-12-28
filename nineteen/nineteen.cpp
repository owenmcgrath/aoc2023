#include "nineteen.h"

void nineteen::solve()
{
    const string INPUT_FILE = "../input/19.txt";
    const string OUTPUT_FILE = "../output/19.txt";

    ifstream inHandle(INPUT_FILE);
    string line;
    WorkflowGraph wg;
    PartList partList;
    if (inHandle.is_open())
    {
        bool gettingParts = false;
        while (getline(inHandle, line))
        {

            if (line == "")
            {
                gettingParts = true;
                continue;
            }

            if (gettingParts)
            {
                Part p;
                int startIdx = 3;
                int endIdx = line.find(',');
                p['x'] = std::stoi(line.substr(startIdx, endIdx - 2));
                startIdx = endIdx + 3;
                endIdx = line.find(',', startIdx);
                p['m'] = std::stoi(line.substr(startIdx, endIdx - startIdx + 1));
                startIdx = endIdx + 3;
                endIdx = line.find(',', startIdx);
                p['a'] = std::stoi(line.substr(startIdx, endIdx - startIdx + 1));
                startIdx = endIdx + 3;
                endIdx = line.find('}', startIdx);
                p['s'] = std::stoi(line.substr(startIdx, endIdx - startIdx + 1));
                partList.push_back(p);
            }
            else
            {
                int wfListStart = line.find('{');
                string wfName = line.substr(0, wfListStart);
                string wfList = line.substr(wfListStart + 1, line.find('}') - wfListStart);
                wfList[wfList.size() - 1] = ',';
                wg[wfName] = {};
                int startPos = 0;
                int splitPos = wfList.find(',');
                while (splitPos != string::npos)
                {
                    string wfStr = wfList.substr(startPos, splitPos - startPos);
                    WorkflowStep wf;
                    parseWorkflow(wfStr, wf);
                    wg[wfName].push_back(wf);
                    startPos = splitPos + 1;
                    splitPos = wfList.find(',', startPos);
                }
            }
        }
    }

    long result1 = sumAcceptedParts(wg, partList);

    WorkflowRanges wfr;
    PartRange r = {{'x', {1, 4000}}, {'m', {1, 4000}}, {'a', {1, 4000}}, {'s', {1, 4000}}};
    generateWorkflowPaths(wg, wfr, r, "in", 0);
    unsigned long result2 = allPossibleCombos(wfr);

    cout << "Solved nineteen " << result1 << ":" << result2 << endl;
}

void nineteen::parseWorkflow(string input, WorkflowStep &wf)
{
    if (input[1] == '>' || input[1] == '<')
    {
        wf.toCompare = input[0];
        wf.comparison = input[1];
        int colonIdx = input.find(':');
        wf.operand = std::stoi(input.substr(2, colonIdx - 2));
        wf.nextWorkflow = input.substr(colonIdx + 1);
    }
    else
    {
        wf.nextWorkflow = input;
    }
}

long nineteen::sumAcceptedParts(const WorkflowGraph &wg, const PartList &partList)
{
    long sum = 0;
    for (auto part : partList)
    {

        string wfName = "in";

        while (!(wfName == "A" || wfName == "R"))
        {
            Workflow wf = wg.at(wfName);
            for (auto wfStep : wf)
            {
                if (wfStep.toCompare == '-')
                {
                    wfName = wfStep.nextWorkflow;
                    break;
                }
                else
                {
                    bool accepted;
                    if (wfStep.comparison == '<')
                    {
                        accepted = part[wfStep.toCompare] < wfStep.operand;
                    }
                    else
                    {
                        accepted = part[wfStep.toCompare] > wfStep.operand;
                    }

                    if (accepted)
                    {
                        wfName = wfStep.nextWorkflow;
                        break;
                    }
                }
            }
        }

        if (wfName == "A")
        {
            for (auto rating : part)
                sum += rating.second;
        }
    }

    return sum;
}

void nineteen::generateWorkflowPaths(const WorkflowGraph &wg, WorkflowRanges &wfPaths, PartRange range, string currWf, int currWfStep)
{
    if (currWf == "A")
    {
        wfPaths.push_back(range);
        return;
    }
    else if (currWf == "R")
    {
        return;
    }
    else
    {
        // update range and push this workflow step on the path
        WorkflowStep ws = wg.at(currWf)[currWfStep];
        if (ws.comparison == '-')
            generateWorkflowPaths(wg, wfPaths, range, ws.nextWorkflow, 0);
        else if (ws.comparison == '>')
        {
            // passing condition
            if (range[ws.toCompare].second > ws.operand)
            {

                PartRange passRange = range;
                passRange[ws.toCompare].first = max(ws.operand + 1, passRange[ws.toCompare].first);
                generateWorkflowPaths(wg, wfPaths, passRange, ws.nextWorkflow, 0);
            }

            // failing condition
            if (range[ws.toCompare].first <= ws.operand)
            {

                PartRange failRange = range;
                failRange[ws.toCompare].second = min(ws.operand, failRange[ws.toCompare].second);
                generateWorkflowPaths(wg, wfPaths, failRange, currWf, currWfStep + 1);
            }
        }
        else if (ws.comparison == '<')
        {
            // passing condition
            if (range[ws.toCompare].first < ws.operand)
            {
                PartRange passRange = range;
                passRange[ws.toCompare].second = min(ws.operand - 1, passRange[ws.toCompare].second);
                generateWorkflowPaths(wg, wfPaths, passRange, ws.nextWorkflow, 0);
            }

            if (range[ws.toCompare].second >= ws.operand)
            {

                // failing condition
                PartRange failRange = range;
                failRange[ws.toCompare].first = max(ws.operand, failRange[ws.toCompare].first);
                generateWorkflowPaths(wg, wfPaths, failRange, currWf, currWfStep + 1);
            }
        }
    }
}

unsigned long nineteen::allPossibleCombos(const WorkflowRanges &ranges)
{
    unsigned long retVal = 0;
    for(auto& range : ranges)
    {
        unsigned long result = 1;
        // check to see if this path is even possible
        bool possible = true;
        for (auto &part : range)
        {
            possible = possible && (part.second.second >= part.second.first);
            result *= (part.second.second - part.second.first + 1);
        }
        if(possible) retVal += result;

    }
    return retVal;
}
