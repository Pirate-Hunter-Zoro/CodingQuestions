#ifndef Solution8_H
#define Solution8_H

#include <algorithm>
#include <vector>

class Solution8{

private:
    /**
     * @brief Convert a matrix of characters into one of integers
     * 
     * @param toCopy 
     * @return std::vector<std::vector<int>> 
     */
    std::vector<std::vector<int>> copyToInt(const std::vector<std::vector<char>> &toCopy)
    {
        std::vector<std::vector<int>> result;
        for (const std::vector<char> &vec : toCopy){
            std::vector<int> row;
            for (char c : vec){
                row.push_back((int)c - 48);
            }
            result.push_back(row);
        }
        return result;
    }

public:
    /**
     * @brief Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
     *
     * @param matrix
     * @return int
     */
    int maximalSquare(const std::vector<std::vector<char>> &matrix)
    {
        std::vector<std::vector<int>> sol = this->copyToInt(matrix);
        int max_square = 0; // set to 1 if any initial squares are 1
        for (int i=0; i<sol.size(); i++){
            if (sol.at(i).at(0) == 1){
                max_square = 1;
                break;
            }
        }
        if (max_square == 0){
            for (int j=0; j<sol.at(0).size(); j++){
                if (sol.at(0).at(j) == 1){
                    max_square = 1;
                    break;
                }
            }
        }

        for (int i = 1; i < sol.size(); i++)
        { // row
            for (int j = 1; j < sol.at(i).size(); j++)
            { // column
                if (matrix.at(i).at(j) == '1')
                {
                    // we can potentially grow this square
                    int prev = std::min(sol.at(i - 1).at(j), std::min(sol.at(i).at(j - 1), sol.at(i - 1).at(j - 1)));
                    prev = (int)sqrt(prev);
                    sol.at(i).at(j) = (prev + 1) * (prev + 1);
                    if (sol.at(i).at(j) > max_square)
                    {
                        max_square = sol.at(i).at(j);
                    }
                }
            }
        }
        return max_square;
    }
};

#endif