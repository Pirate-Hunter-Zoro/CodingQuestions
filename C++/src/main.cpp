#include "include/Solution1.h"
#include "include/Solution2.h"

using namespace std;

int main() {
    
    Solution2 sol = Solution2();
    vector<vector<int> > input;
    vector<int> edge1;
    vector<int> edge2;
    vector<int> edge3;
    vector<int> edge4;
    
    edge1.push_back(0);
    edge1.push_back(1);

    edge2.push_back(1);
    edge2.push_back(2);

    edge3.push_back(2);
    edge3.push_back(0);

    edge4.push_back(1);
    edge4.push_back(3);
    
    input.push_back(edge1);
    input.push_back(edge2);
    input.push_back(edge3);
    input.push_back(edge4);

    vector<vector<int> > output = sol.criticalConnections(4, input);

    return 0;
}