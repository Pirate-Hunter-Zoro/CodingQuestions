import java.io.*;
import java.util.*;

public class RileySolutionSubstringDiff {
    // Let's do this in one array, to optimize our cache performance

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    // 0011 && 0110 -> 0010 (only keeps the bits you care about)
    static int LOWER_MASK = (1 << 16) - 1; // 1 bit in every lower bit position --> 00000000 00000000 11111111 11111111; store string length in lower half
    static int UPPER_MASK = (LOWER_MASK << 16); // 1 bit in every upper bit position; store misses in upper half

    public static int addEditDistance(int x, int addDist) {
        // adding a miss - move it into range
        return x + (addDist << 16);
    }

    public static int addStringLength(int x, int strLength) {
        // string length is already IN the lower bit range
        return x + strLength;
    }

    public static int getEditDistance(int x) {
        // get the actual quantity contained within our double-info 4-byte value
        return (x & UPPER_MASK) >> 16; // get rid of lower bits
    }

    public static int subEditDistance(int x, int addDist) {
        // get the actual quantity contained within our double-info 4-byte value
        return x - (addDist << 16);
    }

    public static int getStrLength(int x) {
        return (x & LOWER_MASK); // get rid of upper bits
    }

    public static int subStringLength(int x, int strLength) {
        return x - strLength;
    }

    public static int extend(int x, int k, int n) {
        int d = k - getEditDistance(x);
        if (getStrLength(x) + d > n){
            d = n - getStrLength(x);
        }
        return addEditDistance(addStringLength(x, d), d);
    }

    public static int shrink(int x, int k) {
        int d = getEditDistance(x) - k;
        return subEditDistance(subStringLength(x, d), d);
    }

    public static void main(String[] args) throws IOException {
        int t = Integer.parseInt(reader.readLine().trim());
        // shared memory beforehand
        int[][] mat = new int[1501][1501];
        for (int l=0; l<t; l++){
            // scan every input
            String[] split = reader.readLine().trim().split(" ");
            int k = Integer.parseInt(split[0].trim());
            String s1 = split[1].trim(), s2 = split[2].trim();

            // iterate over all rows and columns
            for (int i=1; i<=s1.length(); i++){
                for (int j=1; j<=s2.length(); j++){
                    int prev = mat[i-1][j-1];
                    if (s1.charAt(i-1) == s2.charAt(j-1)) {
                        // we have a match - was the previous substring valid?
                        if (getEditDistance(prev) <= k) {
                            // it WAS valid
                            mat[i][j] = addStringLength(prev, 1);
                            continue;
                        } 
                        // previous substring was NOT valid
                        int len = getStrLength(prev); // length of said invalid substring that starts with a match
                        // find the next match
                        int off = 1;
                        while (s1.charAt((i-1) - len + off) != s2.charAt((j-1) - len + off)) {
                            // ignore the first character because it was a match
                            off++; // move along the alignment up until my current place
                        }
                        mat[i][j] = 0;
                        mat[i][j] = addStringLength(mat[i][j], len - off + 1); // you removed an offset number of characters
                        mat[i][j] = addEditDistance(mat[i][j], getEditDistance(prev) - (off - 1)); // subtract the number of mismatches we have removed
                        continue;
                    }
                    // we DO NOT have a match
                    if (getStrLength(prev) > 0) {
                        // we will only take this if we are currently "building" a string
                        // we had a string length of one, and we can add another mismatch
                        mat[i][j] = addStringLength(
                                addEditDistance(prev, 1),
                                1
                            );
                        continue;
                    }
                    mat[i][j] = 0; // move on - no matches in this diagonal so far
                }
                // we have hit the end of one of our columns
                
            }
        }
    }
    
}
