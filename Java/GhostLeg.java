import java.util.*;
import java.io.*;

public class GhostLeg {

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        
        String[] input = reader.readLine().split(" ", 0);
        int[] nm = Arrays.stream(input)
                    .mapToInt(Integer::parseInt)
                    .toArray();
        int numCols = nm[0];
        int numRungs = nm[1];

        int[] rungs = new int[numRungs];
        for (int i=0; i<rungs.length; i++){
            rungs[i] = Integer.parseInt(reader.readLine());
        }

        int[] permuation = new int[numCols];
        // for each column, find where it will map
        for (int col = 1; col <= numCols; col++){
            int currCol = col;
            for (int i=0; i<rungs.length; i++){
                if (currCol == 1 && rungs[i] == 1){
                    // do stuff
                    currCol++;
                } else if (currCol == numCols && rungs[i] == currCol){
                    // do stuff
                    currCol--;
                } else {
                    if (rungs[i] == currCol-1){
                        currCol--;
                    } else if (rungs[i] == currCol){
                        // do stuff
                        currCol++;
                    }
                }
            }
            permuation[currCol-1] = col;
        }

        for (int val : permuation){
            System.out.println(val);
        }

    }
    
}
