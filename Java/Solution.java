import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

public class Solution {

    public static void main(String[] args) {
        ArrayList<Long> coins = new ArrayList<>();
        coins.add((long)2);
        coins.add((long)5);
        coins.add((long)3);
        coins.add((long)6);

        System.out.println(getWays(10, coins));
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

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
        try {
            char[] s1Array = s1.toCharArray();
            char[] s2Array = s2.toCharArray();
        
            int[][][][] matchRecords = new int[s1.length()][s1.length()][s1.length()][s1.length()];

            // base cases - when one of the two strings has no characters to pick from
            for (int i=0; i<s1.length(); i++){
                for (int j=0; j<s1.length(); j++){
                    for (int l=0; l<s1.length(); l++){
                        matchRecords[l][l][i][j] = 0;
                        matchRecords[i][j][l][l] = 0;
                    }
                }
            }

            // first fill up the array with the amount of match differences allowed
            // now that we have that, we actually have to have a BUNCH of these 4D tables for the allowed amount of errors
            int[][][][][] matchRecordsGivenDifferencesAllowed = new int[k+1][s1.length()][s2.length()][s1.length()][s2.length()];
            for (int i=0; i<=k; i++){
                matchRecordsGivenDifferencesAllowed[i] = Arrays.copyOf(matchRecords, matchRecords.length);
            }

            //  now we need to bottom up solve the case where 0 different characters are allowed - that's a 'base case' if you will
            for (int gap=1; gap<=k; gap++){
                if (gap==1){
                    // inner base case
                    for (int i = 0; i < s1.length() - 1; i++) {
                        for (int l = 0; l < s1.length() - 1; l++) {
                            if (s1Array[i] == s2Array[l]){
                                matchRecordsGivenDifferencesAllowed[0][l][l+1][i][i+1] = 1;
                            } else {
                                matchRecordsGivenDifferencesAllowed[0][l][l+1][i][i+1] = 0;
                            }
                        }
                    }
                } else {
                    // no longer inner base case
                    for (int i=0; i < s1.length() - gap; i++) {
                        for (int l=0; l<s1.length()-gap; l++) {
                            if (s1Array[i+gap-1] == s2Array[l+gap-1]){
                                // we could match the most recent character - should we?
                                matchRecordsGivenDifferencesAllowed[0][l][l+gap][i][i+gap] = 
                                                                Math.max(
                                                                    // match the character and move back on both
                                                                    1 + matchRecordsGivenDifferencesAllowed[0][l][l+gap-1][i][i+gap-1],
                                                                    Math.max(
                                                                        // move back along either the first or second string
                                                                        matchRecordsGivenDifferencesAllowed[0][l][l+gap-1][i][i+gap],
                                                                        matchRecordsGivenDifferencesAllowed[0][l][l+gap][i][i+gap-1]
                                                                        )
                                                                    );
                            } else {
                                // we can't match the most recent character - that leaves two choices
                                matchRecordsGivenDifferencesAllowed[0][l][l+gap][i][i+gap] = 
                                                                Math.max(
                                                                    // move back along either the first or second string
                                                                    matchRecordsGivenDifferencesAllowed[0][l][l+gap-1][i][i+gap],
                                                                    matchRecordsGivenDifferencesAllowed[0][l][l+gap][i][i+gap-1]
                                                                    );
                            }
                        }
                    }
                }
            }

            // now do the bottom up traversal for the whole problem
            for (int e=1; e<k; e++){
                // traverse along the number of missing characters allowed
                for (int gap = 1; gap <= k; gap++) {
                    if (gap == 1) {
                        // inner base case
                        for (int i = 0; i < s1.length() - 1; i++) {
                            for (int l = 0; l < s1.length() - 1; l++) {
                                // we are allowed at least one mismatch - by default all of these have length 1
                                matchRecordsGivenDifferencesAllowed[0][l][l + 1][i][i + 1] = 1;
                            }
                        }
                    } else {
                        // no longer inner base case
                        for (int i = 0; i < s1.length() - gap; i++) {
                            for (int l = 0; l < s1.length() - gap; l++) {
                                if (s1Array[i + gap - 1] == s2Array[l + gap - 1]) {
                                    // we could match the most recent character - should we?
                                    matchRecordsGivenDifferencesAllowed[0][l][l + gap][i][i + gap] = Math.max(
                                            // match the character and move back on both
                                            1 + matchRecordsGivenDifferencesAllowed[0][l][l + gap - 1][i][i + gap - 1],
                                            Math.max(
                                                    // move back along either the first or second string
                                                    matchRecordsGivenDifferencesAllowed[0][l][l + gap - 1][i][i + gap],
                                                    matchRecordsGivenDifferencesAllowed[0][l][l + gap][i][i + gap - 1]
                                                )
                                            );
                                } else {
                                    // we can't match the most recent character - that leaves THREE choices
                                    matchRecordsGivenDifferencesAllowed[0][l][l + gap][i][i + gap] = Math.max(
                                            Math.max(
                                                // move back along either the first or second string without costing any error
                                                matchRecordsGivenDifferencesAllowed[e][l][l + gap - 1][i][i + gap],
                                                matchRecordsGivenDifferencesAllowed[e][l][l + gap][i][i + gap - 1]
                                            ),
                                            // take the mismatch and see if taking it led to a better solution
                                            matchRecordsGivenDifferencesAllowed[e-1][l][l+gap-1][i][i+gap-1]
                                        );
                                }
                            }
                        }
                    }
                }
            }

            return matchRecordsGivenDifferencesAllowed[k][0][s1.length() - 1][0][s2.length() - 1];

        } catch (NullPointerException e){
            return -1;
        } catch (NegativeArraySizeException e){
            return -2;
        }
    }

}