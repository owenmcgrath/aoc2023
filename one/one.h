#ifndef ONE_H
#define ONE_H

#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include "ctype.h"
#include "../lib/trie.h"

using namespace std;

class one
{
    public:

        one(){}
        
        static void solve();

    private:

        static void buildTrie(Trie& t);
        static void buildStrToVal(unordered_map<string,int>& t);


        template <class iter>
        static int getFirstDigitPart2(unordered_map<string, int>& strToVal, Trie& trie, iter it, iter end);

        template <class iter, class constiter>
        static int getFirstDigitPart1(iter it, constiter end);

        static unordered_map<string, int> strToVal;
        static Trie trie;
};

#endif