package main;

import report.Report;

import java.io.FileNotFoundException;

public class Main {
  public static void main(String[] args) throws FileNotFoundException {
    var rp = new Report("taxes.txt");
    System.out.println(rp);
  }
}
