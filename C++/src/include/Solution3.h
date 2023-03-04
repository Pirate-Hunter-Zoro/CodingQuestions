#ifndef Solution3_H
#define Solution3_H

#include <string>
#include <vector>
#include <iostream>

class Solution3 {

    public:
        /**
         * @brief Determine the minimum number of cuts (number of partitions - 1) to divide s into a set of palindromes
         * 
         * @param s 
         * @return int 
         */
        int minCut(std::string s){
            int n = s.length();
            int* solutions = (int*) malloc(n * sizeof(int));
            for (int i=0; i<n; i++){
                solutions[i] = i;
            }

            // now loop through the rest of the string to determine if the current character is a palindrome
            for (int i=1; i<n; i++){
                // we need to find all of the cuts that end with the newest character making a palindrome, and the subproblem  is whatever comes before
                for (int j=0; j<i; j++){
                    int moveBack = 0;
                    int moveUp = 0;
                    while (s[i - moveBack] == s[j + moveUp]){
                        moveBack++;
                        moveUp++;
                        if (i - moveBack <= j + moveUp){
                            // we achieved a valid palindrome
                            if (j==0) // palindrome from beginning
                                solutions[i] = 0;
                            else // not so much
                                solutions[i] = std::min(solutions[i], 1 + solutions[j-1]);
                            break;
                        }
                    }
                }
                solutions[i] = std::min(solutions[i], 1 + solutions[i-1]);
            }

            // now return our final solution
            int answer = solutions[n-1];
            delete[] solutions;
            return answer;

        }

}; 

#endif