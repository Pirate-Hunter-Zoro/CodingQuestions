#include "include/Solution1.h"
#include "include/Solution2.h"

using namespace std;

int main() {
    
    Solution2 sol = Solution2();
    vector<vector<int> > input;
    vector<int> edge1;
    vector<int> edge2;
    vector<int> edge3;
    
    edge1.push_back(2);
    edge1.push_back(1);
    edge1.push_back(1);

    edge2.push_back(2);
    edge2.push_back(3);
    edge2.push_back(1);

    edge3.push_back(3);
    edge3.push_back(4);
    edge3.push_back(1);
    
    input.push_back(edge1);
    input.push_back(edge2);
    input.push_back(edge3);

    cout << sol.networkDelayTime(input, 4, 1);

    return 0;
}