import java.util.*;
import java.io.*;

public class Solution {

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws Exception {
        // Coin change problem
        ArrayList<Long> coinsList = new ArrayList<>();
        coinsList.add((long)2);
        coinsList.add((long)5);
        coinsList.add((long)3);
        coinsList.add((long)6);
        System.out.println(getWays(10, coinsList));

        // longest common "substring" problem
        System.out.println(substringDiff(2, "tabriz", "torino"));

        // unbounded knapsack
        ArrayList<Integer> weights = new ArrayList<>();
        weights.add(3);
        weights.add(4);
        weights.add(4);
        weights.add(4);
        weights.add(8);
        System.out.println(unboundedKnapsack(9, weights));

    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * This is Dr. Ian Riley (from Tulsa University)'s method for this problem
     * @param n
     * @param m
     * @param coins
     * @return
     */
    public static long solve(int n, int m, int[] coins) {
        Arrays.sort(coins);
        long[][] cache = new long[n+1][m+1];
        for (int j=0; j<m+1; j++){
            cache[0][j] = 0;
        }
        for (int i=0; i<n+1; i++){
            cache[i][0] = 0;
        }
        for (int i=1; i<=n; i++){
            for (int j=2; j<=m; j++){
                if (coins[j-1]>i) {
                    // can't include this coin
                    cache[i][j] = cache[i][j-1];
                } else if (coins[j-1] == i) {
                    cache[i][j] = 1 + cache[i][j-1];
                } else {
                    // number of ways to include this coin PLUS the number of ways to NOT include this coin
                    cache[i][j] = 
                    cache[i - coins[j-1]][j] // coins has not been formatted correctly
                    // coins[j-1] is SMALLER than i because we are in this section of the conditional
                        + cache[i][j-1];
                }
            }
        }

        return cache[n][m];
    }

    /**
     * Given an amount and the denominations of coins available, determine how many ways change can be made for amount. There is a limitless supply of each coin type.

    Example


    There are  ways to make change for : , , and .

    Function Description

    Complete the getWays function in the editor below.

    getWays has the following parameter(s):

    int n: the amount to make change for
    int c[m]: the available coin denominations
    Returns

    int: the number of ways to make change
     * @param n
     * @param c
     * @return
     */
    public static long getWays(int n, List<Long> c) {
        // there is one way to match 0 cents - the empty set
        long[][] numWays = new long[n+1][c.size()];
        long[] coins = new long[c.size()];
        Arrays.sort(coins);
        int currentIdx = 0;
        for (long val : c){
            coins[currentIdx++] = val;
        }

        for (int i=0; i<coins.length; i++){
            numWays[0][i] = 1;
            // regardless of how many coins we are allowed, this is how many ways there are to match zero cents
        }

        // now for the bottom up dynamic programming
        for (int i=1; i<numWays.length; i++){
            for (int j=0; j<numWays[i].length; j++){
                int cents = i;
                long coinVal = coins[j];
                // we are only allowed to use coins from coins[0-j] (inclusive)
                if (coinVal > cents){
                    // we can't use this coin
                    if (j>0){
                        numWays[i][j] = numWays[i][j-1];
                    } else {
                        numWays[i][j] = 0;
                    }
                } else {
                    // we can match the coin - add however many ways there are with THOSE cents remaining
                    if (j>0){
                        numWays[i][j] = numWays[i][j-1] + numWays[i-(int)coinVal][j];
                        // the number of ways WITH using this coin PLUS those without
                    } else {
                        numWays[i][j] = numWays[i-(int)coinVal][j];
                        // we can ONLY consider the possibility of using this coin
                    }
                }
            }
        }

        return numWays[n][c.size()-1];
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * Complete the 'substringDiff' function below. It should return an
     * integer that represents the length of the longest common substring as
     * defined.
     * link: https://www.hackerrank.com/challenges/substring-diff/problem
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     * 1. INTEGER k - by how many characters the two substrings are allowed to vary
     * 2. STRING s1
     * 3. STRING s2
     * SAME LENGTH STRINGS
     */

    public static int substringDiff(int k, String s1, String s2) {
        // https://programs.programmingoneonone.com/2021/07/hackerrank-substrings-diff-problem-solution.html
        // TOO SLOW

        // https://www.hackerrank.com/amir_holtzman
        // THIS person showed a fast enough algorithm

        // greedily finding the longest common substring and going from there does not work
        int maxLength = 0;

        for (int i=0; i<s1.length(); i++){
            for (int j=0; j<s2.length(); j++){
                int mismatches = 0;
                int length = 0;
                for (int l=0; i+l<s1.length() && j+l<s2.length(); l++){
                    if (s1.charAt(i+l) != s2.charAt(j+l)){
                        // mismatch
                        mismatches++;
                    } 
                    if (mismatches > k){
                        break;
                    } else {
                        length++;
                    }
                }
                if (mismatches < k) {
                    // reached end of one string before hitting mismatch limit
                    for (int l=1; i-l>=0 && j-l>=0; l++){
                        // go back the other way
                        if (s1.charAt(i-l) != s2.charAt(j-l)){
                            // mismatch
                            mismatches++;
                        } 
                        if (mismatches > k){
                            break;
                        } else {
                            length++;
                        }
                    }
                }
                // now best possible length has been achieved
                maxLength = Math.max(maxLength, length);
            }
        }
        // return the record
        return maxLength;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * Complete the 'unboundedKnapsack' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     * 1. INTEGER k
     * 2. INTEGER_ARRAY arr
     */
    public static int unboundedKnapsack(int k, List<Integer> arr) {
        // first convert to an array and sort it
        int[] objectWeights = arr.stream()
                        .mapToInt(num -> num)
                        .toArray();
        Arrays.sort(objectWeights);

        // Write your code here
        int[][] table = new int[k+1][objectWeights.length];
        // top row is capacity 0 - leave it alone

        // base cases for top row
        if (objectWeights[0] == 1){
            // we have 1's across out top row
            for (int i=0; i<objectWeights.length; i++){
                table[1][i] = 1;
            }
        }

        // base cases for left-most column
        for (int r=1; r<=k; r++){
            table[r][0] = r - (r % objectWeights[0]);
        }

        // now for the dynamic programming aspect
        for (int capacity=2; capacity<=k; capacity++){
            for (int j=1; j<objectWeights.length; j++){
                if (objectWeights[j] > capacity){
                    // we cannot use this object - it is too heavy so take the best solution NOT using this coin
                    table[capacity][j] = table[capacity][j-1];
                } else {
                    // we CAN use this object - but should we? 
                    // we know whether we do or don't, our ultimate set of items WILL fit in the bag, so take the max of the values yielded by the two choices
                    table[capacity][j] = Math.max(table[capacity][j-1], objectWeights[j] + table[capacity-objectWeights[j]][j]);
                }
            }
        }

        // return target cell
        return table[k][objectWeights.length-1];
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

}