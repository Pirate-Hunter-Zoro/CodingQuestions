#include "include/Solution1.h"
#include "include/Solution2.h"
#include "include/Solution3.h"
#include "include/Solution4.h"

using namespace std;

int main() {
    
    Solution4 sol = Solution4();
    vector<vector<int> > dungeon;
    vector<int> row;
    row.push_back(-3);
    row.push_back(5);
    dungeon.push_back(row);
    cout << sol.calculateMinimumHP(dungeon) << endl;

    return 0;
}