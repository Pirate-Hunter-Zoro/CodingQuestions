#ifndef Solution5_H
#define Solution5_H

#include <math.h>
#include <stdlib.h>
#include <vector>

class Solution5
{
private:
    std::vector<int> factorials;
    std::vector<int> num_ones_given_free_digits;

public:
    Solution5(){
        this->factorials.push_back(1);
        this->num_ones_given_free_digits.push_back(0);
    }

    int factorial(int n)
    {
        if (this->factorials.size() - 1 >= n)
        {
            return this->factorials.at(n);
        }
        else
        {
            this->factorials.push_back(this->factorial(n - 1) * n);
            return this->factorials.at(n);
        }
    }

    int choose(int n, int k)
    {
        return (this->factorial(n) / ((this->factorial(k) * this->factorial(n - k))));
    }

    /**
     * @brief Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
     *
     * @param k
     * @return int
     */
    int numOnesGivenFreeDigits(int k)
    {
        if (this->num_ones_given_free_digits.size() - 1 >= k)
        {
            return this->num_ones_given_free_digits.at(k);
        }
        // otherwise
        int num_ones = 0;
        for (int i = 1; i <= k; i++)
        {
            num_ones += i * this->choose(k, i);
        }
        this->num_ones_given_free_digits.push_back(num_ones);
        return num_ones;
    }

    int countDigitOne(int n)
    {
        if (n == 0)
        {
            return 0;
        }
        int num_digits = (int)(log(n) / log(10)) + 1; // log base 10 of the number plus 1
        int num_ones_lower_length = this->numOnesGivenFreeDigits(num_digits - 1);

        // now we need to consider this last digit
        int k = num_digits - 1;
        int current = n;
        for (int i = k; i > 0; i--)
        {
            current = current / 10;
        }

        int num_ones = current * num_ones_lower_length + 1 + this->countDigitOne(n - current * ((int)pow(10, num_digits - 1)));
        return num_ones;
    }
};

#endif