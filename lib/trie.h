#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>

using namespace std;


struct TrieNode
{
    TrieNode() : leaves(), val('\r') {}
    unordered_map<char, TrieNode *> leaves;
    char val;
    bool end;
};

typedef unordered_map<char, TrieNode*> Trie;

class TrieHelper
{
public:
    static void addWordToTrie(Trie& t, const string& s);
};

#endif