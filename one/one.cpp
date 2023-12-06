#include "one.h"

unordered_map<string,int> one::strToVal;
Trie one::trie;

void one::solve()
{
    string line;
    ifstream input("../input/1.txt");
    ofstream output("../output/1.txt");
    int sumPart1 = 0;
    int sumPart2 = 0;

    unordered_map<string, int> strToVal = unordered_map<string, int>();
    Trie trie = Trie();
    buildStrToVal(strToVal);
    buildTrie(trie);

    if (input.is_open())
    {
        while (getline(input, line))
        {

            int lVal1 = getFirstDigitPart1(line.begin(), line.end());
            int rVal1 = getFirstDigitPart1(line.rbegin(), line.rend());
            sumPart1 += (10 * (lVal1)) + rVal1;

            int lVal2 = getFirstDigitPart2(strToVal, trie, line.begin(), line.end());
            int rVal2 = getFirstDigitPart2(strToVal, trie, line.rbegin(), line.rend());
            sumPart2 += (10 * lVal2) + rVal2;
            std::cout << line << " " << lVal1 << rVal1 << ":" << lVal2 << rVal2 << std::endl;
        }
    }
    input.close();
    output << sumPart1 << std::endl;
    output << sumPart2 << std::endl;

    output.close();
    std::cout << "Solved one: " << sumPart1 << ":" <<  sumPart2 << ::endl;
}

void one::buildTrie(Trie &t)
{

    TrieHelper::addWordToTrie(t, "one");
    TrieHelper::addWordToTrie(t, "two");
    TrieHelper::addWordToTrie(t, "three");
    TrieHelper::addWordToTrie(t, "four");
    TrieHelper::addWordToTrie(t, "five");
    TrieHelper::addWordToTrie(t, "six");
    TrieHelper::addWordToTrie(t, "seven");
    TrieHelper::addWordToTrie(t, "eight");
    TrieHelper::addWordToTrie(t, "nine");
    TrieHelper::addWordToTrie(t, "eno");
    TrieHelper::addWordToTrie(t, "owt");
    TrieHelper::addWordToTrie(t, "eerht");
    TrieHelper::addWordToTrie(t, "ruof");
    TrieHelper::addWordToTrie(t, "evif");
    TrieHelper::addWordToTrie(t, "xis");
    TrieHelper::addWordToTrie(t, "neves");
    TrieHelper::addWordToTrie(t, "thgie");
    TrieHelper::addWordToTrie(t, "enin");
}

void one::buildStrToVal(unordered_map<string, int> &t)
{
    t["one"] = 1;
    t["two"] = 2;
    t["three"] = 3;
    t["four"] = 4;
    t["five"] = 5;
    t["six"] = 6;
    t["seven"] = 7;
    t["eight"] = 8;
    t["nine"] = 9;
    t["eno"] = 1;
    t["owt"] = 2;
    t["eerht"] = 3;
    t["ruof"] = 4;
    t["evif"] = 5;
    t["xis"] = 6;
    t["neves"] = 7;
    t["thgie"] = 8;
    t["enin"] = 9;
}

template <class iter>
int one::getFirstDigitPart2(unordered_map<string, int>& strToVal, Trie& trie, iter it, iter end)
{

    TrieNode* trieIt = nullptr;
    string ss(5, '\0');
    auto ssIt = ss.begin();
    iter wordBegin;
    bool wordBeginSet = false;

    while (it != end)
    {
        if (isdigit(*it))
        {
            return *it - '0';
        }
        else
        {
            int test = trieIt == nullptr ? -1 : trieIt->leaves.count(*it);
            if (trieIt != nullptr && trieIt->leaves.count(*it))
            {
                trieIt = trieIt->leaves[*it];
                *ssIt = *it;
                ssIt++;
                
            }
            else 
            {
                trieIt = nullptr;
                ssIt = ss.begin();
                if(wordBeginSet)
                {
                    it = wordBegin + 1;
                    wordBeginSet = false;
                }

            }
            if (trieIt == nullptr && trie.count(*it))
            {
                trieIt = trie[*it];
                *ssIt = *it;
                ssIt++;
                wordBegin = it;
                wordBeginSet = true;
            }

            if (trieIt != nullptr && trieIt->end)
            {
                string numStr(wordBegin, it + 1);
                return strToVal[numStr];
            }
        }
        it++;
    };

    return -1;
}

template <class iter, class constiter>
int one::getFirstDigitPart1(iter it, constiter end)
{
    while (it != end && !isdigit(*it)) it++;
    
    return it== end ? 0 : *it - '0';
}
