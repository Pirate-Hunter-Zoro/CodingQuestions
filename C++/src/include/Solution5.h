#ifndef Solution5_H
#define Solution5_H

#include <math.h>
#include <stdlib.h>
#include <vector>

class Solution
{
public:
    std::vector<int> factorials;
    int factorial(int n)
    {
        if (factorials.size() - 1 >= n)
        {
            return factorials.at(n);
        }
        else
        {
            factorials.push_back(factorial(n - 1) * n);
            return factorials.at(n);
        }
    }

    int choose(int n, int k)
    {
        return (factorial(n) / ((factorial(k) * factorial(n - k))));
    }

    std::vector<int> num_ones_given_free_digits;
    int numOnesGivenFreeDigits(int k)
    {
        if (num_ones_given_free_digits.size() - 1 >= k)
        {
            return num_ones_given_free_digits.at(k);
        }
        // otherwise
        int num_ones = 0;
        for (int i = 1; i <= k; i++)
        {
            num_ones += i * choose(k, i);
        }
        num_ones_given_free_digits.push_back(num_ones);
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
        int num_current_ones = 0;
        int k = num_digits - 1;
        int current = n;
        for (int i = k; i > 0; i--)
        {
            current = current / 10;
        }

        int num_ones = current * num_ones_lower_length + this->countDigitOne(n - current * ((int)pow(10, num_digits - 1)));
        return num_ones;
    }
};

#endif