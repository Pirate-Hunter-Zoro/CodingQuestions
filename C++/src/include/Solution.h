#ifndef Solution_h
#define Solution_h

#include "TreeNode.h"
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<utility>

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class Solution {

public:

    // scramble string
    bool isScramble(const std::string &s1, const std::string &s2);
    bool isScrambleTopDown(const std::string &s1, const std::string &s2, std::unordered_map<std::pair<std::string,std::string>, bool, pair_hash> &scrambles);

    // number of possible binary trees
    int numTrees(int n);

    // actual set of possible binary trees
    std::vector<TreeNode *> generateTrees(int n);
    std::vector<TreeNode *> generateTreesBU(int n, std::vector<std::vector<TreeNode *> > &allPossibilities);
    TreeNode *addToAll(TreeNode *treeNode, int k);
    std::vector<TreeNode *> copyTreeNodePointers(const std::vector<TreeNode *> &oldPointers);
    TreeNode *copyTree(TreeNode *oldTreePointer);

    // number of distinct subsequences in string s that can form the string t
    int numDistinct(const std::string &s, const std::string &t);
    int numDistinctTopDown(const std::string &s, int i, const std::string &t, int j, std::vector<std::vector<int> > &cache);

    // the row of pascal's triangle for the right index
    std::vector<int> getRow(int rowIndex);
    int choose(int n, int k);

    // minimum path sum through a triangle from top to bottom
    int minimumTotal(std::vector<std::vector<int> > &triangle);

    // maximum profit given a set of stock prices on each given day
    int maxProfit(std::vector<int> &prices);
    // https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/
    // https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

    // unhappy friends - related to stable matching problem
    // https://leetcode.com/problems/count-unhappy-friends/
    int unhappyFriends(int n, std::vector<std::vector<int> > &preferences, std::vector<std::vector<int> > &pairs);

    // construct a binary tree from preorder (self, left, right) and inorder (left, self, right) traversal
    TreeNode* buildTree(std::vector<int> &preorder, std::vector<int> &inorder);
    TreeNode* buildTreeByIndex(std::vector<int> &preorder, int preorderStart, int preorderEnd, std::vector<int> &inorder, int inorderStart, int inorderEnd);

    // coin change problem
    // https://leetcode.com/problems/coin-change/
    int coinChange(std::vector<int> &coins, int amount);
};

#endif