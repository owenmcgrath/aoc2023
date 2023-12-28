#ifndef NINETEEN_H
#define NINETEEN_H

#include "../lib/loadInput.h"
#include <iostream>
#include <utility>
#include <math.h>
#include <vector>
#include <unordered_map>


using namespace std;

struct WorkflowStep
{
    char toCompare; //'x' 'm' 'a' or 's'
    char comparison; //'>' or '<'
    int operand; 
    string nextWorkflow;

    WorkflowStep():  toCompare('-'), comparison('-'), operand(-1), nextWorkflow(""){}
};

typedef vector<WorkflowStep> Workflow;

typedef unordered_map<string, Workflow> WorkflowGraph;

typedef unordered_map<char, int> Part;
typedef vector<Part> PartList;

typedef unordered_map<char, pair<int,int>> PartRange;
typedef vector<PartRange> WorkflowRanges;

class nineteen 
{
public:

    static void solve();
    static void parseWorkflow(string input, WorkflowStep& wf);
    static long sumAcceptedParts(const WorkflowGraph& wg, const PartList& partList);
    static void generateWorkflowPaths(const WorkflowGraph& wg, WorkflowRanges& wfPaths, PartRange range, string currWf, int currWfStep);
    static unsigned long allPossibleCombos(const WorkflowRanges& ranges);
};

#endif