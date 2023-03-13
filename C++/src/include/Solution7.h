#ifndef Solution7_H
#define Solution7_H

#include <string>
#include <stack>

class Solution7
{

private:
    /**
     * @brief Helper method to determine the longest inner palindrome substring of a string
     *
     * @param s
     * @return std::string
     */
    std::string longestPalindromeFromStart(const std::string &s)
    {
        std::string pal;
        if (s.size() <= 1)
        {
            pal = s;
        }
        else
        {
            int record = 1; // length of the longest palindrome that starts from the beginning
            std::vector<std::vector<bool>> table;
            for (int r = 0; r < s.size(); r++)
            {
                std::vector<bool> row;
                for (int c = 0; c < s.size(); c++)
                {
                    row.push_back(false);
                }
                table.push_back(row);
            }

            // now the table is set up
            for (int p = 0; p < table.size()-1; p++)
            {
                // base cases
                table.at(p).at(p) = true;
                table.at(p).at(p + 1) = s.at(p) == s.at(p + 1);
            }

            // now solve the problem
            for (int offset = 2; offset < s.size(); offset++)
            {
                for (int r = 0; r < s.size() - offset; r++)
                {
                    if (s.at(r) == s.at(r + offset))
                    {
                        // then trim off the first and last characters and check that case
                        table.at(r).at(r + offset) = table.at(r + 1).at(r + offset - 1);
                    }
                    else
                    {
                        table.at(r).at(r + offset) = false;
                    }
                }
            }

            // now go across the first row to find the longest palindrome starting at the beginning of the string
            for (int c = 1; c < table.at(0).size(); c++)
            {
                if (table.at(0).at(c))
                {
                    record = c + 1;
                }
            }

            // now we have the length of the longest substring within s starting at the beginning
            pal = s.substr(0, record);
        }
        return pal;
    }

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
        std::string shortestPalindrome(const std::string &s)
        {
            if (s.size() == 1)
            {
                return s;
            }
            else
            {
                std::string pal_s = this->longestPalindromeFromStart(s);
                std::stack<char> following_letters;
                for (int i = pal_s.size(); i < s.size(); i++)
                {
                    following_letters.push(s.at(i));
                }
                // now pop the stack into another string which you will concatenate with s
                std::string front;
                while (!following_letters.empty())
                {
                    front += following_letters.top();
                    following_letters.pop();
                }
                return front + s;
            }
    }
};

#endif