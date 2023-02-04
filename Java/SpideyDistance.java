import java.util.*;
import java.io.*;

public class SpideyDistance {

    static BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static long gcd(long a, long b) {
        while (b > 0) {
            long tmp = a;
            a = b;
            b = tmp % b;
        }
        return a;
    }

    public static void main(String args[]) throws IOException {

        // input
        long[] nm = Arrays.stream(reader.readLine().trim().split(" "))
                    .mapToLong(Long::parseLong)
                    .toArray();
        
        // taxi distance
        long n = nm[0];

        // spidey distance
        long m = nm[1];

        // Truck distance (t+(t-1))*4 + 1

        long numerator = 2*n*(n+1) + 1;

        long m1 = (m+1) - (m+1) % 3;
        long denominator = 2*m*(m+1) + 1 + 4 * ((m1*(m1 - 3))/6 + m1/3*((m+1)%3));

        long reduce = gcd(numerator, denominator);
        numerator /= reduce;
        denominator /= reduce;
        
        if (numerator == denominator) {
            System.out.println("1");
        } else {
            System.out.println(numerator + "/" + denominator);
        }

    }
}
