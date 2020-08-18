#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>
#include "HW3.h"

//Stav Rones
//001201196

using namespace std;
using namespace chrono;

int main() {
  Dec2Bin db;
  db.readDecNum();
  cout << "The binary number using recursive method = ";
  db.dec2bin_rcv(db.decNum);
  cout << "\nThe binary number using iterative method = ";
  db.dec2bin_itr();

  //Problem2
  cout <<  endl << "-------- PROBLEM 2 -------" << endl << endl;
  //array of test variables for the functions
  int n[] = {1,3,5,16,24,26,30};
  //create prob2 object
  Problem2 prob2;
  int arg;

  //table header
  cout << left
   << setw(5) << "n"
   << setw(20) << "F1"
   << setw(20) << "F2"
   << setw(20) << "F3"
   << endl
   << setw(5) << "==="
   << setw(20) << "==="
   << setw(20) << "==="
   << setw(20) << "==="
   << endl;

   //iterate through each number and test it with each function
  for(int i=0;i<7;i++){
    arg = n[i];
    cout << left
    << setw(5) << arg
    << setw(20) << prob2.F1(arg)
    << setw(20) << prob2.F2(arg)
    << setw(20) << prob2.F3(arg)
    << endl;
  }

  cout << endl << "Each function returns 2^n:" << endl
  << "Tiem Complexity: " << endl
  << "  F1: O(log(n))" << endl
  << "  F2: O(n)" << endl
  << "  F2: O(2^n)" << endl
  << "Therefor, the worse run time is F3" << endl << endl;


  //Problem 3
  cout << "-------- PROBLEM 3 -------" << endl << endl;
  int n1[] = {5,10,20,30,40};

  //table header
  cout << left
     << setw(5) << "n"
     << setw(20) << "Recursion"
     << setw(20) << "Dynamic Recursion"
     << setw(30) << "Runtime1 (microseconds)"
     << setw(30) << "Runtime2 (microseconds)"
     << endl
     << setw(5) << "==="
     << setw(20) << "==="
     << setw(20) << "==="
     << setw(30) << "==="
     << setw(30) << "==="
     << endl;

     //iterate through test cases and apply to both methods
    for(int j=0;j<5;j++){
      arg = n1[j];
      //constructor initiates a dynamic array of size n
      Problem3* pr3 = new Problem3(arg);

      cout << left << setw(5) << arg;

      //keep track of time before first program
      auto t0 = high_resolution_clock::now();
      cout << left << setw(20) << pr3->fibonacci_rec(arg);

      //keep track of time between programs
      auto t1 = high_resolution_clock::now();
      cout << setw(20) << pr3->fibonacci_rec_dyn(arg);

      //keep track of time after second program
      auto t2 = high_resolution_clock::now();

      //calcualte program run times
      auto duration1 = duration_cast<microseconds>(t1- t0);
      auto duration2 = duration_cast<microseconds>(t2 - t1);
      cout << left
      << setw(30) << duration1.count()
      << setw(30) << duration2.count()
      << endl;
    }

    cout << "\nThe runtime of the purely recursive method is O(2^n)." << endl
    << "With the help of a dynamic array that keeps track of which numbers " << endl
    << "were already calculated recursion, this cuts the runtime down significantly" << endl
    << "because the time complexity is now O(n)" << endl << endl;

    return 0;
}
