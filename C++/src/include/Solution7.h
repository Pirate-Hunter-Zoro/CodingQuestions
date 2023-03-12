#ifndef Solution7_H
#define Solution7_H

#include <string>

class Solution7
{
public:
    /**
     * @brief You are given a string s.
     * You can convert s to a palindrome by adding characters in front of it.
     * Return the shortest palindrome you can find by performing this transformation.
     * https://leetcode.com/problems/shortest-palindrome/description/
     *
     * @param s
     * @return std::string
     */
    std::string shortestPalindrome(std::string s)
    {
        if (s.size() == 1 || this->isPalindrome(s)){
            return s;
        } else {
            std::string pal_s = s;

            while (!this->isPalindrome(pal_s)){
                
            }
        }
    }

    /**
     * @brief Helper method to determine if a string is a palindrome
     * 
     * @param s 
     * @return true 
     * @return false 
     */
    bool isPalindrome(const std::string &s){
        if (s.size() == 1){
            return true;
        } else {
            for (int i = 0; i<s.size()/2; i++){
                if (s.at(i) != s.at(s.size()-1-i)){
                    return false;
                }
            }
            return true;
        }
    }
};

#endif