#ifndef Solution1_H
#define Solution1_H

#include "ListNode.h"
#include <stack>

class Solution1 {

private:
    /**
     * @brief Reverse the order of the next k nodes in the linked list segment
     * 
     * @param current 
     * @param k 
     * @return ListNode* 
     */
    ListNode* invert(ListNode* current, int k){
        // we need to create a stack of nodes, and unpop the stack to reverse the order
        std::stack<ListNode*> reversed_order;
        ListNode* toReturn;
        ListNode* toFollow;
        ListNode* currentNode = current;
        for (int i=0; i<k; i++){
            if (i < k-1){
                // not the last one
                reversed_order.push(currentNode);
                currentNode = currentNode->next;
            } else{
                // last one
                toReturn = currentNode;
                toFollow = currentNode->next;
            }
        }

        ListNode* previous = toReturn;
        ListNode* nextNode;
        // now unpop the stack
        while (!reversed_order.empty()){
            nextNode = reversed_order.top(); // peek
            previous->next = nextNode;
            reversed_order.pop(); // pop
            previous = nextNode;

            if (reversed_order.empty()){
                // last one
                nextNode->next = toFollow;
            }
        }

        return toReturn;
    }

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

    /**
     * @brief Reverse every k group of nodes - if the lenght of the linked list is not divisible by k leave the last group of nodes untouched
     * 
     * @param head 
     * @param k 
     * @return ListNode* 
     */
    ListNode* reverseKGroup(ListNode* head, int k) {
        // first find the length of the linked list
        ListNode* current = head;
        int length = 0;
        while (current != nullptr){
            length++;
            current = current->next;
        }

        // now that we have the length
        ListNode* toReturn = head;
        ListNode* lastCurrent;
        current = head;
        for (int i=0; i<length / k; i++){
            if (i==0) {
                // keep track of the node to return
                toReturn = this->invert(current, k);
            } else {
                // just invert
                lastCurrent->next = this->invert(current, k);
            }
            lastCurrent = current;
            current = current->next;
        }

        // now that the inversion is done
        return toReturn;

    }
};

#endif