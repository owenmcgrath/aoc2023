#include "nine.h"

void nine::solve()
{

    // get i/o file handles
    ifstream input("../input/9.txt");
    ofstream output("../output/9.txt");

    string line;
    vector<long long> values;
    long long result1 = 0;
    long long result2 = 0;
    // get each line from the input
    while (getline(input, line))
    {
        // split each line by integer and push all the values into a vector
        istringstream lineSs(line);
        int count = 0;
        while (!lineSs.eof())
        {
            if (count >= values.size())
                values.push_back(0);
            lineSs >> values[count++];
        }

        // since we predict in place to save space, clone for each
        vector<long long> history(values);
        result1 += predictReading(values);
        result2 += predictHistory(history);
    }

    std::cout << "Solved nine: " << result1 << ":" << result2 << std::endl;
    output << result1 << std::endl;
    output << result2 << std::endl;
}

long long nine::predictReading(vector<long long> &values)
{
    int diffSeqLen = values.size();
    bool allZeros = false;

    // loop through each array length
    for (diffSeqLen; diffSeqLen > 0 && !allZeros; diffSeqLen--)
    {
        allZeros = true;
        // from the beginning loop until one before the end
        for (int j = 0; j < diffSeqLen - 1; j++)
        {
            // calculate the difference between the one ahead and store in this array
            values[j] = values[j + 1] - values[j];

            // check if this row has all zeros to meet the loop break condition
            allZeros = allZeros && values[j] == 0;
        }
    }
    values.front() = 0; // in case we get all the way to the last possible val, it must be zero
    long long result = 0;

    // with each rows prediction calculated, sum the predictions to get the original prediction
    for (int k = diffSeqLen - 1; k < values.size(); k++)
        result += values[k + 1];
    return result;
}

long long nine::predictHistory(vector<long long> &values)
{
    int diffSeqLen = values.size();
    bool allZeros = false;

    // loop through each array length
    for (diffSeqLen; diffSeqLen > 0 && !allZeros; diffSeqLen--)
    {
        allZeros = true;

        // from the end, loop backwards until one before the beginning
        for (int j = values.size() - 1; j > (values.size() - diffSeqLen); j--)
        {
            // calculate the difference between the one ahead and store in this array
            values[j] = values[j] - values[j - 1];
            allZeros = allZeros && values[j] == 0;
        }
    }
    values.back() = 0; // in case we get all the way to the last possible val, it must be zero
    long long result = 0;
    
    // sum each history estimate by iterating from the beginning of the last generated sequence, 
    // subtracting the result by the first value
    for (int k = values.size() - diffSeqLen - 1; k >= 0; k--)
        result = values[k] - result;
    return result;
}
