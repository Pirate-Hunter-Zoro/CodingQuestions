import java.io.*;
import java.util.*;

public class ClassFieldTrip {

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException{
        String s1 = reader.readLine();
        String s2 = reader.readLine();

        StringBuilder merged = new StringBuilder();
        int s1Idx = 0;
        int s2Idx = 0;
        while (s1Idx < s1.length() && s2Idx < s2.length()) {
            if (s1.charAt(s1Idx) <= s2.charAt(s2Idx)) {
                merged.append(s1.substring(s1Idx, s1Idx + 1));
                s1Idx++;
            } else {
                merged.append(s2.substring(s2Idx, s2Idx + 1));
                s2Idx++;
            }
        }

        if (s1Idx < s1.length()) {
            while (s1Idx < s1.length()) {
                merged.append(s1.substring(s1Idx, s1Idx + 1));
                s1Idx++;
            }
        } else if (s2Idx < s2.length()) {
            while (s2Idx < s2.length()) {
                merged.append(s2.substring(s2Idx, s2Idx + 1));
                s2Idx++;
            }
        }

        System.out.println(merged.toString().trim());
    }
    
}
