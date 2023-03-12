#ifndef Solution4_H
#define Solution4_H

#include<iostream>
#include<vector>

class Solution4{

public:
    /**
     * @brief The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. 
     * The dungeon consists of m x n rooms laid out in a 2D grid. 
     * Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.
     * The knight has an initial health point represented by a positive integer. 
     * If at any point his health point drops to 0 or below, he dies immediately.
     * Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).
     * To reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.
     * Return the knight's minimum initial health so that he can rescue the princess.
     * Note that any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
     *
     * @param dungeon
     * @return int
     */
    int calculateMinimumHP(std::vector<std::vector<int> > &dungeon)
    {
        std::vector<std::vector<int> > health;
        for (std::vector<int> row : dungeon)
            health.push_back(row);
        // now we have a full table to fill out

        // initialization of bottom right square
        int row = dungeon.size() - 1;
        int col = dungeon.at(row).size() - 1;
        int endValue = dungeon.at(row).at(col);
        if (endValue < 0)
        {
            health.at(row).at(col) = 1 - endValue;
        }
        else
        {
            health.at(row).at(col) = 1;
        }

        // bottom row
        for (int i = col - 1; i >= 0; i--)
        {
            int val = dungeon.at(row).at(i);
            int previousHealth = health.at(row).at(i + 1);
            if (val >= 0)
            {
                health.at(row).at(i) = std::max(previousHealth - val, 1);
            }
            else
            {
                health.at(row).at(i) = previousHealth - val;
            }
        }

        // right column
        for (int j = row - 1; j >= 0; j--)
        {
            int val = dungeon.at(j).at(col);
            int previousHealth = health.at(j + 1).at(col);
            if (val >= 0)
            {
                health.at(j).at(col) = std::max(previousHealth - val, 1);
            }
            else
            {
                health.at(j).at(col) = previousHealth - val;
            }
        }

        // now we are ready to traverse to the top left square
        for (int r = row - 1; r >= 0; r--)
        {
            for (int c = col - 1; c >= 0; c--)
            {
                int bottomHealth = health.at(r + 1).at(c);
                int rightHealth = health.at(r).at(c + 1);
                int lowerHealth = std::min(bottomHealth, rightHealth);
                int val = dungeon.at(r).at(c);
                if (val >= 0)
                {
                    health.at(r).at(c) = std::max(lowerHealth - val, 1);
                }
                else
                {
                    health.at(r).at(c) = lowerHealth - val;
                }
            }
        }

        // return the final minimum health needed
        return health.at(0).at(0);
    }
};

#endif