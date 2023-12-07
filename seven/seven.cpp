#include "seven.h"

void seven::solve()
{
    string line;
    ifstream input("../input/7.txt");
    ofstream output("../output/7.txt");

    vector<multimap<string,int>> ranks;
    vector<multimap<string,int>> jokerRanks;

    for(int i = 0; i < 7; i++){ 
        ranks.push_back(multimap<string,int>());
        jokerRanks.push_back(multimap<string, int>());
    }

    if(input.is_open())
    {
        while(getline(input, line))
        {
            unordered_map<char, int> charMap;
            int bid = 0;
            string hand = line.substr(0,5);
            parseHand(line, charMap, bid);
            insertHand(charMap, hand, bid, ranks);
            insertHand(charMap, hand, bid, jokerRanks, true);


        }

        int result1 = calculateWinnings(ranks);
        int result2 = calculateWinnings(jokerRanks);

        std::cout << "Solved two: " << result1 << ":" <<  result2 << std::endl;
        output << result1 << std::endl;
        output << result2 << std::endl;


        input.close();
        output.close();
    }
}

void seven::parseHand(const string& handAndBid, unordered_map<char,int>& hand, int& bid)
{
    int idx = 0;
    while(handAndBid[idx] != ' ')
    {
        hand[handAndBid[idx++]]++;
    }
    idx++;
    bid = 0;
    while(idx < handAndBid.size() && handAndBid[idx] != ' ')
    {
        bid*=10;
        bid+= handAndBid[idx++] - '0';
    }
}

void seven::insertHand(const unordered_map<char,int>& hand, const string& handStr, int bid, vector<multimap<string, int>>& ranks, bool joker)
{
    int twoPairCount = 0;
    bool hasThreeOfAKind = false;
    int maxOfAKind = 0;
    int jokerCount = 0;
    for(auto& card : hand)
    {
        if(card.second == 2 && card.first != 'J') twoPairCount++;
        hasThreeOfAKind = card.second == 3 || hasThreeOfAKind;
        if(card.first == 'J') jokerCount = card.second;
        if(!joker || card.first != 'J') maxOfAKind = max(maxOfAKind, card.second);
    }

    if(joker && jokerCount > 0)
    {
        /*
        J2323 -> full house
        JJJ23 -> 4 of a kind
        2JJ33 -> 4 of a kind
        333JJ -> full house

        */
        if(twoPairCount == 2 && maxOfAKind == 2) hasThreeOfAKind = true; //case where J is the lone ranger with a two pair
        else maxOfAKind += jokerCount;
        //a hand that has a joker converted to a full house or a two pair will always be weaker than the maxOfAKind equivalent
    }

    int mapIdx = 0;

    //full house
    if(hasThreeOfAKind && twoPairCount == 1)
    {
        mapIdx = 4;
    }
    else if(twoPairCount == 2)
    {
        mapIdx = 2;
    }
    else 
    {
        switch(maxOfAKind)
        {
            case 1: 
                mapIdx = 0;
                break;
            case 2:
                mapIdx = 1;
                break;
            case 3:
                mapIdx = 3;
                break;
            case 4:
                mapIdx = 5;
                break;
            case 5:
                mapIdx = 6;
                break;
            default: return;
        }
    }

    string convStr;
    for(auto& c : handStr)
    {
        char cToAdd = c;
        if(!isdigit(c))
        {
            switch(c)
            {
                case 'T':
                    cToAdd ='9' + 1;
                    break;
                case 'J':
                    cToAdd= joker ? '2' - 1 : '9' + 2;
                    break;
                case 'Q':
                    cToAdd= '9' + 3;
                    break;
                case 'K':
                    cToAdd= '9' + 4;
                    break;
                case 'A':
                    cToAdd= '9' + 5;
                    break;
            }
        }
        convStr += cToAdd;
    }

    ranks[mapIdx].insert(pair<string,int>(convStr, bid));

}

unsigned long seven::calculateWinnings(const vector<multimap<string,int>>& ranks)
{
    int ctr = 1;
    unsigned long total = 0;
    for(auto& mmap : ranks)
    {
        for(auto& hand: mmap)
        {
            
            total += (ctr++)*hand.second;
            cout << total << endl;
        }
    }

    return total;
}