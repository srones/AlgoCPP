#ifndef HW03_H
#define HW03_H
#include <iostream>
#include <string>

//Stav Rones
//001201196

using namespace std;

//class for problem 1
class Dec2Bin{
public:
  int decNum;
  Dec2Bin() : decNum(0) {};
  void readDecNum();
  void dec2bin_rcv(int d);
  void dec2bin_itr();
};

//class for problem 2 that has public functions with each given function
class Problem2{
public:
  int F1(int n) {
      if (n == 0) return 1;
      if (n % 2 == 0) {
        int result = F1(n / 2);
        return result * result;
      }
      else return 2 * F1(n-1);
  }

  int F2(int n) {
    if (n == 0) return 1;
    return 2 * F2(n-1);
  }

  int F3(int n){
    if (n == 0) return 1;
    return F3(n-1) + F3(n-1);
  }
};

//class for problem 3
class Problem3{
  int* arr;
public:
  //constructor creates a dynamic array of size n
  //and fills it with -1's to indicate they have not been visited
  Problem3(int n){
    arr = new int[n];
    fillArr(n);}
  ~Problem3(){delete[] arr;}
  void fillArr(int n){
    for(int i=0;i<n;i++){
      arr[i] = -1;
    }
  }//two recursive methods
  int fibonacci_rec(int n);
  int fibonacci_rec_dyn(int n);
};


//stack class from class
template<class ItemType>
class StackInterface{
  public :
virtual bool isEmpty() const = 0;
virtual bool push( const ItemType& newEntry) = 0;
virtual bool pop() = 0;
virtual ItemType peek() const = 0;
};


template<class ItemType>
class ArrayStack : public StackInterface<ItemType>{
private:
  static const int DEFAULT_CAPACITY= 50;
  ItemType items[DEFAULT_CAPACITY]; // Array of stack items
  int top; // Index to top of stack
public:
  ArrayStack(); // Default constructor
  bool isEmpty() const;
  bool push(const ItemType& newEntry);
  bool pop();
  ItemType peek() const;
};

#endif
