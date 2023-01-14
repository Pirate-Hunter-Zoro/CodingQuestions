#include "include/Solution.h"

using namespace std;

/**
 * @brief We can scramble a string s to get a string t using the following algorithm:

If the length of the string is 1, stop.
If the length of the string is > 1, do the following:
Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
Apply step 1 recursively on each of the two substrings x and y.
Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.
 *
 * @param s1
 * @param s2
 * @return true
 * @return false
 */
bool Solution::isScramble(const string &s1, const string &s2) {

    // dummy case
    if (s1.size() != s2.size()) {
        return false;
    }

    // we need something to store all of the solutions we have found
    unordered_map<pair<string,string>, bool, pair_hash> scrambles;

    return this->isScrambleTopDown(s1, s2, scrambles);

}

/**
 * @brief Helper (recursive) function to actually determine if two strings are scrambles of each other
 * 
 * @param s1 
 * @param s2 
 * @param scrambles 
 * @return true 
 * @return false 
 */
bool Solution::isScrambleTopDown(const string &s1, const string &s2, unordered_map<pair<string, string>, bool, pair_hash> &scrambles)
{
    pair<string, string> queryPair;
    queryPair.first = s1;
    queryPair.second = s2;
    // first, have we already found the solution?
    if (scrambles.find(queryPair) != scrambles.end()) {
        return (*(scrambles.find(queryPair))).second;
    }

    // now we actually have work to do
    if (s1 == s2) {
        scrambles.insert({queryPair, true});
        return true;
    } else if (s1.size() == 1) {
        scrambles.insert({queryPair, false});
        return false;
    } else {
        for (int i=1; i<s1.size(); i++) {
            // get our strings ready

            // don't switch order with splice
            string first1A = s1.substr(0, i);
            string second1A = s2.substr(0,i);
            string first1B = s1.substr(i, s1.size());
            string second1B = s2.substr(i, s2.size());

            // DO switch order with splice
            string first2A = s1.substr(i, s1.size());
            string second2A = s2.substr(0, s2.size()-i);
            string first2B = s1.substr(0, i);
            string second2B = s2.substr(s2.size() - i, s2.size());
            
            if (this->isScrambleTopDown(first1A, second1A, scrambles) && this->isScrambleTopDown(first1B, second1B, scrambles)){
                scrambles.insert({queryPair, true});
                return true;
            }
            else if (this->isScrambleTopDown(first2A, second2A, scrambles) && this->isScrambleTopDown(first2B, second2B, scrambles)) {
                scrambles.insert({queryPair, true});
                return true;
            }
        }
        scrambles.insert({queryPair, false});
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Given an integer n, return the NUMBER of structurally unique binary search trees possible with node values {1,2,...,n}
 * 
 * @param n 
 * @return int 
 */
int Solution::numTrees(int n)
{
    vector<int> numTrees;
    for (int i = 0; i < n; i++)
    {
        numTrees.push_back(0);
    }
    // base case - one node to play with
    numTrees.at(0) = 1;

    for (int i = 1; i < n; i++)
    {
        // we have 'i+1' nodes to play with
        int total = 0;

        // root is 1 - that leaves 'i' nodes to play with for the right subtree
        total += numTrees.at(i - 1);

        // 1 < root <= i
        for (int j = 2; j <= i; j++)
        {
            // root is j - that leaves 'j-1' nodes to play with for the left subtree, and 'i+1-j' nodes to play with for the right subtree
            total += numTrees.at(j - 1 - 1) * numTrees.at(i - j);
        }

        // root is i+1 - that leaves 'i' nodes to play with for the left subtree
        total += numTrees.at(i - 1);

        numTrees.at(i) = total;
    }

    return numTrees.at(n - 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n.
 * Return the answer in any order.
 * 1 <= n <= 8
 *
 * @param n
 * @return vector<TreeNode*>
 */
vector<TreeNode*> Solution::generateTrees(int n) {
    // stores all possible trees given a number of values, concatenated from a certain column from the above table (all possible root values)
    vector<vector<TreeNode*> > allPossibilities;
    for (int i=0; i<n; i++){
        vector<TreeNode*> emptyPointerVector;
        allPossibilities.push_back(emptyPointerVector);
    }

    // use helper method
    return this->generateTreesBU(n, allPossibilities);
}

/**
 * @brief Helper bottom up dynamic programming method to solve the 'all possible BSTs' problem
 * 
 * @param n 
 * @param solutions 
 * @return vector<TreeNode*> 
 */
vector<TreeNode*> Solution::generateTreesBU(int n, vector<vector<TreeNode*> > &allPossibilities) {
    // base case
    allPossibilities.at(0).push_back(new TreeNode);
    *(allPossibilities.at(0).at(0)) = TreeNode(1);

    // solve our problem
    for (int j=1; j<n; j++){
        int numNodes = j+1;

        // first, for the root node equalling 1 (no left children possible):
        vector<TreeNode *> possibleRights = this->copyTreeNodePointers(allPossibilities.at(numNodes - 1 - 1));
        for (TreeNode *rightTreePointer : possibleRights)
        {
            TreeNode *newTreePointer = new TreeNode;
            *newTreePointer = TreeNode(1, nullptr, this->addToAll(rightTreePointer, 1));
            allPossibilities.at(j).push_back(newTreePointer);
        }

        // now, a middle value root node, with both types of children being possible
        for (int i=1; i<j; i++){
            int rootVal = i+1;
            vector<TreeNode*> possibleLefts = allPossibilities.at(i-1);
            vector<TreeNode*> possibleRights = this->copyTreeNodePointers(allPossibilities.at(numNodes-rootVal-1));
            for (TreeNode* leftTreePointer : possibleLefts) {
                for (TreeNode* rightTreePointer : possibleRights) {
                    TreeNode* newTreePointer = new TreeNode;
                    *newTreePointer = TreeNode(rootVal, leftTreePointer,  this->addToAll(rightTreePointer, rootVal));
                    allPossibilities.at(j).push_back(newTreePointer);
                }
            }
        }

        // now, for the root node equalling j+1 (no right children possible):
        vector<TreeNode*> possibleLefts = allPossibilities.at(j-1);
        for (TreeNode* leftTreePointer : possibleLefts) {
            TreeNode* newTreePointer = new TreeNode;
            *newTreePointer = TreeNode(j+1, leftTreePointer, nullptr);
            allPossibilities.at(j).push_back(newTreePointer);
        }
    }

    // return the list of TreeNode pointers
    return allPossibilities.at(n-1);
    
}

/**
 * @brief Helper method to add all values in a binary tree
 * 
 * @param treeNode
 * @param k 
 * @return TreeNode* 
 */
TreeNode* Solution::addToAll(TreeNode* treeNode, int k) {
    // allocate some storage for a new TreeNode
    TreeNode* newTreePointer = new TreeNode;

    // the TreeNode which this pointer points to is a copy of the TreeNode the input pointer points to
    *newTreePointer = TreeNode(treeNode->val+k);

    // now we need to look left
    if (treeNode->left != nullptr){
        newTreePointer->left = new TreeNode;
        newTreePointer->left = this->addToAll(treeNode->left, k);
    }

    // now look right
    if (treeNode->right != nullptr){
        newTreePointer->right = new TreeNode;
        newTreePointer->right = this->addToAll(treeNode->right, k);
    }

    // return the new TreeNode pointer
    return newTreePointer;

}

/**
 * @brief Helper method to copy a vector of pointers to TreeNodes without changing any of the original pointers
 * 
 * @param oldPointers 
 * @return vector<TreeNode*> 
 */
vector<TreeNode*> Solution::copyTreeNodePointers(const vector<TreeNode*> &oldPointers) {
    vector<TreeNode*> newNodes;
    for (TreeNode* oldPointer : oldPointers) {
        TreeNode* newPointer = this->copyTree(oldPointer);
        newNodes.push_back(newPointer);
    }
    return newNodes;
}

/**
 * @brief Helper (recursive) method to copy the tree which the input tree pointer points to, returned as a pointer
 * 
 * @param oldTreePointer 
 * @return TreeNode 
 */
TreeNode* Solution::copyTree(TreeNode* oldTreePointer) {
    if (oldTreePointer == nullptr){
        return nullptr;
    } else {
        TreeNode* newTreePointer = new TreeNode;
        *newTreePointer = TreeNode(oldTreePointer->val, this->copyTree(oldTreePointer->left), this->copyTree(oldTreePointer->right));
        return newTreePointer;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Given two strings s and t, return the number of distinct
subsequences of s which equals t.
 *
 * @param s
 * @param t
 * @return int
 */
int Solution::numDistinct(const string &s, const string &t) {

    // create our cache
    vector<vector<int> > cache;
    for (int i=0; i<s.size(); i++){
        vector<int> row;
        for (int j=0; j<t.size(); j++){
            row.push_back(-1);
        }
        cache.push_back(row);
    }

    return this->numDistinctTopDown(s, 0, t, 0, cache);

}

/**
 * @brief Top down recursive helper to solve the number of distinct subsequences of 's' that make up 't' problem
 * 
 * @param s 
 * @param i 
 * @param t 
 * @param j 
 * @param cache
 * @return int 
 */
int Solution::numDistinctTopDown(const string &s, int i, const string &t, int j, vector<vector<int> > &cache) {

    // base cases
    if (j >= t.size())
    {
        // only one way to match an empty string - with an empty subsequence
        return 1;
    }
    else if (i >= s.size())
    {
        // if I have no characters to pick from, I can't match a non-empty t
        return 0;
    } else if (cache[i][j] != -1)
    {
        // check to make sure we have not solved this problem
        return cache[i][j];
    } else {
        // now we gotta solve the problem
        int numPossibleSolutions;
        if (s.substr(i, 1) == t.substr(j, 1))
        {
            // then we have a couple of options
            numPossibleSolutions = this->numDistinctTopDown(s, i + 1, t, j + 1, cache) + this->numDistinctTopDown(s, i + 1, t, j, cache);
            // explore the two possibilities of either letting this current character match, or not letting it match
        }
        else
        {
            // we only have one choice - progress i because it did not match
            numPossibleSolutions = this->numDistinctTopDown(s, i + 1, t, j, cache);
        }
        cache[i][j] = numPossibleSolutions;
        return numPossibleSolutions;
    }
        
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.
 *
 * @param rowIndex
 * @return vector<int>
 */
vector<int> Solution::getRow(int rowIndex){
    vector<int> row;

    for (int i=0; i<=rowIndex; i++){
        row.push_back(this->choose(rowIndex, i));
    }

    return row;
}

/**
 * @brief Given n distinct items, return the number of ways in which you can choose a group of k items out of them
 * 
 * @param n 
 * @param k 
 * @return int 
 */
int Solution::choose(int n, int k){
    if (k > n) {
        return 0;
    } else {
        // keep things as small as possible as we go
        int numerator = 1; // n * (n-1) * (n-2) * ... * (k+1)
        int denominator = 1; // (n-k) * (n-k-1) * ... * 2 * 1
        
        int bottom = 2;
        // iteration while keeping integers small
        for (int top=n; top >= k+1; top--){
            numerator *= top;
            while (bottom <= n-k){
                denominator *= bottom;
                if (numerator % denominator == 0){
                    numerator /= denominator;
                    denominator = 1;
                }
                bottom++;
            }
        }

        // result
        return numerator / denominator;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Given a triangle array, return the minimum path sum from top to bottom.
 * For each step, you may move to an adjacent number of the row below.
 * More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.
 *
 * @param triangle
 * @return int
 */
int Solution::minimumTotal(vector<vector<int> > &triangle) {

    // setup for our bottom up approach
    vector<vector<int> > solutions;
    for (int i=0; i<triangle.size(); i++){
        vector<int> row;
        for (int j=0; j<triangle.at(triangle.size()-1).size(); j++){
            // just copy the last row for our bottom up approach
            row.push_back(triangle.at(triangle.size() - 1).at(j));
        }
        solutions.push_back(row);
    }

    // now solve the problem - go to second to last row
    for (int k=triangle.size()-1-1; k>=0; k--){
        for (int l=triangle.at(k).size()-1; l>=0; l--){
            solutions.at(k).at(l) = triangle.at(k).at(l) + min(solutions.at(k+1).at(l), solutions.at(k+1).at(l+1));
        }
    }

    return solutions.at(0).at(0);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 *
 * @param prices
 * @return int
 */
int Solution::maxProfit(vector<int> &prices)
{
    int maxProfit = 0;
    int maxVal = prices.at(prices.size() - 1);

    for (int i = prices.size() - 2; i >= 0; i--)
    {
        maxProfit = max(maxProfit, maxVal - prices.at(i));
        maxVal = max(maxVal, prices.at(i));
    }

    return maxProfit;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief You are given a list of preferences for n friends, where n is always even.
 * For each person i, preferences[i] contains a list of friends sorted in the order of preference. In other words, a friend earlier in the list is more preferred than a friend later in the list. Friends in each list are denoted by integers from 0 to n-1.
 * All the friends are divided into pairs. The pairings are given in a list pairs, where pairs[i] = [xi, yi] denotes xi is paired with yi and yi is paired with xi.

 * However, this pairing may cause some of the friends to be unhappy. A friend x is unhappy if x is paired with y and there exists a friend u who is paired with v but:
 * x prefers u over y, and
 * u prefers x over v.
 * 
 * Return the number of unhappy friends.
 * @param n
 * @param preferences
 * @param pairs
 * @return int
 */
int Solution::unhappyFriends(int n, vector<vector<int> > &preferences, vector<vector<int> > &pairs){
    int numUnhappy = 0;



    return numUnhappy;
}