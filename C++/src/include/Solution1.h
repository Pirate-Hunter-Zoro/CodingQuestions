#ifndef Solution1_H
#define Solution1_H

#include "ListNode.h"

class Solution1 {

public:
    ListNode *swapPairs(ListNode *head)
    {
        ListNode *toReturn = head;

        ListNode *current = head;
        bool first = true;
        while (current != nullptr && current->next != nullptr)
        {
            ListNode *second = current->next;
            current->next = second->next;
            second->next = current;
            
            ListNode* nextCurrent = current->next;
            if (nextCurrent != nullptr && nextCurrent->next != nullptr){
                // we'll have another pair after this, so we need to send 'current's forward pointer to whatever nextCurrent's forward pointer points to
                current->next = nextCurrent->next;
            }
            current = nextCurrent;
            if (first)
            {
                toReturn = second;
                first = false;
            }
        }

        return toReturn;
    }
};

#endif