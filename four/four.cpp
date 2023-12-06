#include "four.h"

void four::solve()
{
    const string INPUT_FILE = "../input/4.txt";
    const string OUTPUT_FILE = "../output/4.txt";

    vector<string> input;
    LoadInput::load(INPUT_FILE, input);

    int result1 = 0;
    int result2 = 0;

    vector<int> copies(input.size(), 1);

    int count = 0;
    for(auto& card : input)
    {
        unordered_set<int> winners;
        vector<int> numbers;
        parseCard(card, winners, numbers);

        int result = calculateScore(winners, numbers);
        result1 += result;
        
        int matches = numWinners(winners, numbers);
        for(int i = 0; i < matches; i++)
        {
            copies[i+count+1] += copies[count];
        }
        result2 += copies[count];
        count++;
        cout << card << " | " << result << ":" <<  copies[count] << endl;
    }

    ofstream output(OUTPUT_FILE);
    output << result1 << endl;
    output << result2 << endl;

    cout << "Solved four " << result1 << ":" << result2 << endl;
}

void four::parseCard(const string& card, unordered_set<int>& winners, vector<int>& numbers)
{
    size_t it = card.find(":")+2;

    while(card[it] != '|')
    {
        int winner = 0;
        while(card[it] == ' ') it++;
        while(card[it] != ' ')
        {
            winner *=10;
            winner += (card[it]-'0');
            it++;
        }
        winners.insert(winner);
        it++;
    }
    it+=2;
    while(it < card.length())
    {
        int number = 0;
        while(card[it] == ' ') it++;
        while(it < card.length() && card[it] != ' ')
        {
            number *=10;
            number += (card[it]-'0');
            it++;
        }
        numbers.push_back(number);
        it++;
    }
}

int four::calculateScore(const unordered_set<int>& winners, vector<int>& numbers)
{
    int score = 0;
    for(auto& number : numbers)
    {
        if(winners.count(number) > 0)
        {
            score = score == 0 ? 1 : score*=2;
        }
    }
    return score;
}

int four::numWinners(const unordered_set<int>& winners, vector<int>& numbers)
{
    int count = 0;
    for(auto& number : numbers)
    {
        if(winners.count(number) > 0)
        {
            count++;
        }
    }
    return count;
}