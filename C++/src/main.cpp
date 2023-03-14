#include "include/Solution1.h"
#include "include/Solution2.h"
#include "include/Solution3.h"
#include "include/Solution4.h"
#include "include/Solution5.h"
#include "include/Solution6.h"
#include "include/Solution7.h"
#include "include/Solution8.h"

using namespace std;

int main() {
    
    // Solution5 sol = Solution5();
    // cout << sol.countDigitOne(25) << endl;

    Solution8 sol = Solution8();
    vector<vector<char>> input{
        {'1', '1', '1', '1', '0'},
        {'1', '1', '1', '1', '0'},
        {'1', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'0', '0', '1', '1', '1'}
    };
    cout << sol.maximalSquare(input);

    return 0;
}