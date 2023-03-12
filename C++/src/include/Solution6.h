#ifndef Solution6_H
#define Solution6_H

#include <vector>
#include <cstdlib>

class Solution6
{
public:
    /**
     * @brief You are a professional robber planning to rob houses along a street. 
     * Each house has a certain amount of money stashed. 
     * All houses at this place are arranged in a circle. 
     * That means the first house is the neighbor of the last one. 
     * Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
     * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
     *
     * @param nums
     * @return int
     */
    int rob(std::vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return nums.at(0);
        }
        if (nums.size() == 2)
        {
            return std::max(nums.at(0), nums.at(1));
        }

        int *sol1 = (int *)malloc((nums.size() - 1) * sizeof(int)); // disallow last house
        sol1[0] = nums.at(0);
        sol1[1] = std::max(nums.at(0), nums.at(1));
        for (int i = 2; i < nums.size() - 1; i++)
        {
            sol1[i] = std::max(nums.at(i) + sol1[i - 2], sol1[i - 1]);
        }

        int *sol2 = (int *)malloc((nums.size() - 1) * sizeof(int)); // disallow first house
        sol2[0] = nums.at(1);
        sol2[1] = std::max(nums.at(1), nums.at(2));
        for (int i = 3; i < nums.size(); i++)
        {
            sol2[i] = std::max(nums.at(i) + sol2[i - 3], sol2[i - 2]);
        }

        return std::max(sol1[nums.size() - 2], sol2[nums.size() - 2]);
    }
};

#endif