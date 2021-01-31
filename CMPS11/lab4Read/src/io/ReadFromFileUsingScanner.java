package io;

import java.io.File;
import java.util.Scanner;
public class ReadFromFileUsingScanner
{
  public static void main(String[] args) throws Exception
  {
    // pass the path to the file as a parameter
    // File file = new File("wiktionary.txt");
    File file = new File(args[0]);
    Scanner sc = new Scanner(file);
    String line = "";
    long N = sc.nextLong(); 
    long weight;
    String query;
    while (sc.hasNextLong())  {
        weight = sc.nextLong();
        query  = sc.next();
        System.out.println(weight + " " + query);
    }
    sc.close();
  }
}