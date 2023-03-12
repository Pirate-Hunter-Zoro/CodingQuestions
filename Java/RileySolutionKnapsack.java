import java.io.*;
import java.util.*;

public class RileySolutionKnapsack {
    // create a more efficient reader than a Scanner
    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException{
        int T = Integer.parseInt(reader.readLine().trim());

        int[] prevCol = new int[2001];
        int[] currCol = new int[2001];
        // max input size for knapsack capacity is 2000 - but include an extra space because we want to include 0

        for (int t = 0; t < T; t++){
            // read in data
            int[] nk = Arrays
                .stream(reader.readLine().trim().split(" "))
                .mapToInt(Integer::parseInt)
                .toArray();
            int n = nk[0]; int k = nk[1];
            int[] arr = Arrays
                .stream(reader.readLine().trim().split(" "))
                .mapToInt(Integer::parseInt)
                .toArray();
            Arrays.sort(arr);

            // solve
            for (int j=1; j<=n; j++){
                // go over all columns

                // swapzies
                int[] tmp = prevCol;
                prevCol = currCol;
                currCol = tmp;

                // solve for rows - leave the first row alone
                for (int i=1; i<=k; i++){
                    if (arr[j-1] > i) {
                        // this stone is too large to fit into our current backpack
                        currCol[i] = prevCol[i];
                    } else {
                        currCol[i] = Math.max(
                            prevCol[i], // don't pick
                            currCol[i-arr[j-1]] + arr[j-1] // do pick
                            );
                    }
                }
            }
            System.out.printf("%d\n", currCol[k]);
            if (t+1 < T) {
                for (int i=1; i<=k; i++){
                    // reset (technicaly only need to reset current)
                    prevCol[i] = 0;
                    currCol[i] = 0;
                }
            }   
        }
    }
}