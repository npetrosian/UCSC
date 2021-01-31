package problem6;

public class problem6 {
public static int getValue(int a, int b, int n){
int x, c;
System.out.println("arrive: a = " + a + " b = " + b); c = (a+b)/2;
if( c*c <= n ){
x = c; }else{
x = getValue(a, c-1, n); }
System.out.println("depart: a = " + a + " b = " + b);
return x; }
public static void main(String[] args){ System.out.println(getValue(3, 13, 5));
} }
