#include "include/Solution1.h"

using namespace std;

int main() {
    
    ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    Solution1 sol = Solution1();
    sol.reverseKGroup(head, 3);

    return 0;
}