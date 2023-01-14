#include "include/Solution.h"

using namespace std;

int main() {

    Solution solution = Solution();

    cout << boolalpha;
    cout << solution.isScramble("abcdbdacbdac", "bdacabcdbdac") << endl << endl;

    vector<TreeNode*> possibleTrees = solution.generateTrees(3);
    cout << possibleTrees.size() << endl;
    cout << solution.numTrees(3) << endl << endl;

    string s = "rabbbit";
    string t = "rabbit";
    cout << solution.numDistinct(s, t) << endl << endl;

    cout << solution.choose(5, 3) << endl; // 10
    cout << solution.choose(5, 0) << endl; // 1
    cout << solution.choose(5, 1) << endl; // 5
    cout << solution.choose(5, 5) << endl; // 1
    cout << solution.choose(0, 0) << endl; // 1
    cout << solution.choose(3, 4) << endl; // 0
    for (int val : solution.getRow(4)){
        cout << val << " ";
    }
    cout << endl << endl;

    vector<vector<int> > triangle {
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3}
    };
    cout << solution.minimumTotal(triangle) << endl << endl; // 11

    return 0;
}