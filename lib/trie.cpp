#include "trie.h"

void TrieHelper::addWordToTrie(Trie &t, const string &s)
{
    auto it = s.cbegin();
    if (t.count(*it) == 0) t[*it] = new TrieNode();
    TrieNode* nodeRef = t[*it];
    nodeRef->val = *it;
    it++;
    while (it != s.cend())
    {
        if (nodeRef->leaves.count(*it) == 0)
        {
            nodeRef->leaves[*it] = new TrieNode();
            nodeRef->leaves[*it]->val = *it;
            nodeRef->leaves[*it]->end = false;

        }
        nodeRef = nodeRef->leaves[*it];
        it++;
    }
    nodeRef->end = true;
}