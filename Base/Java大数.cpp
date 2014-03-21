import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        BigInteger a,b,c;
        int n;
        Scanner cin = new Scanner(System.in);
        n = cin.nextInt();
        for (int i = 1; i <= n; i ++){
            if (i != 1){
                System.out.println();
            }
            a = cin.nextBigInteger();
            b = cin.nextBigInteger();
            c = a.add(b);
            System.out.println("Case "+i+":");
            System.out.println(a+" + "+b+" = "+c);
        }
    }
}