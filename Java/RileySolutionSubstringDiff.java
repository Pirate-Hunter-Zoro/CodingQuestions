import java.io.*;
import java.util.*;

public class RileySolutionSubstringDiff {
    // Let's do this in one array, to optimize our cache performance

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    // 0011 && 0110 -> 0010 (only keeps the bits you care about)
    static int LOWER_MASK = (1 << 16) - 1; // 1 bit in every lower bit position --> 00000000 00000000 11111111 11111111; store string length in lower half
    static int UPPER_MASK = (LOWER_MASK << 16); // 1 bit in every upper bit position; store misses in upper half

    public static int addEditDistance(int x, int addDist) {
        return x + (addDist << 16);
    }

    public static int addStringLength(int x, int strLength) {
        return x + strLength;
    }

    public static int getEditDistance(int x) {
        return (x & UPPER_MASK) >> 16; // get rid of lower bits
    }

    public static int getStrLength(int x) {
        return (x & LOWER_MASK); // get rid of upper bits
    }

    public static void main(String[] args) throws IOException {
        int t = Integer.parseInt(reader.readLine().trim());
        // shared memory beforehand
        int[][] mat = new int[1501][1501];
        for (int i=0; i<t; i++){
            // scan every input
            String[] split = reader.readLine().trim().split(" ");
            int k = Integer.parseInt(split[0].trim());
            String s1 = split[1].trim(), s2 = split[2].trim();
        }
    }
    
}
