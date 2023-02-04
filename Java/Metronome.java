import java.io.*;
import java.util.*;

public class Metronome {

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException{
        
        int numTicks = Integer.parseInt(reader.readLine());

        double numTurns = (double) numTicks / 4.0;

        String output;
        if (numTurns % 4 == 0){
            output = String.format("%.1f", numTurns);
        } else {
            output = String.format("%.2f", numTurns);
        }
        
        System.out.println(output);
    
    }
    
}
