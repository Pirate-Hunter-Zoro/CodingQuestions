import java.io.*;
import java.util.*;

public class RileySolutionLego {
    
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    static final long MOD = 1_000_000_007;

    public static void main(String[] args) throws IOException {
        int t = Integer.parseInt(reader.readLine().trim());
        long[][] mat = new long[3][1001];

        // mat[0] is our base row
        mat[0][1] = 1; mat[0][2] = 2; mat[0][3] = 4; mat[0][4] = 8;// base row, all buildings, all solutions
        for (int i=5; i<=1000; i++){
            mat[0][i] = RileySolutionLego.add(mat[0][i], mat[0][i - 1]);
            mat[0][i] = RileySolutionLego.add(mat[0][i], mat[0][i - 2]);
            mat[0][i] = RileySolutionLego.add(mat[0][i], mat[0][i - 3]);
            mat[0][i] = RileySolutionLego.add(mat[0][i], mat[0][i - 4]);
        }

        for (int tk=1; tk<=t; tk++) {
            int[] split = Arrays
                        .stream(reader.readLine().trim().split(" "))
                        .mapToInt(Integer::parseInt)
                        .toArray();
            int n = split[0];
            int m = split[1];

            // mat[1] is all combinations
            for (int nk = 1; nk <= n; nk++) {
                for (int i=1; i<=m; i++) {
                    if (nk == 1) {
                        mat[1][i] = mat[0][i];
                        continue;
                    }
                    mat[1][i] = RileySolutionLego.mul(mat[1][i], mat[0][i]);
                }
            }
            // mat[2] is the solutions
            for (int i=1; i<=m; i++) {
                mat[2][i] = RileySolutionLego.sub(
                        mat[1][i],
                        RileySolutionLego.sum(mat[2], mat[1], i) // all those bad layouts we don't want to count
                    );
            }
            System.out.printf("%d\n", mat[2][m]);
        }
    }

    /**
     * By mod class - our special way of addition
     * @param a
     * @param b
     * @return
     */
    public static long add(long a, long b) {
        return (a + b) % RileySolutionLego.MOD;
    } 

    /**
     * By mod class - our special way of multiplication
     * @param a
     * @param b
     * @return
     */
    public static long mul(long a, long b) {
        return (a * b) % RileySolutionLego.MOD;
    }

    public static long sub(long a, long b) {
        if (a < b) {
            return (a + RileySolutionLego.MOD - b) % RileySolutionLego.MOD;
        }
        return (a - b) % RileySolutionLego.MOD;
    }

    public static long sum(long[] S, long[] A, int w) {
        if (w <= 1) {
            // no breaks came before
            return 0;
        }
        long sumBads = 0;
        for (int i=1; i<=w-1; i++){
            sumBads = RileySolutionLego.add(
                                sumBads,
                                RileySolutionLego.mul(S[i], A[w-i])
                                );
        }
        return sumBads;
    }

}
