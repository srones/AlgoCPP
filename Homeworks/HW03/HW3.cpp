#include <iostream>
#include <string>
#include <math.h> //log2()
#inlcude <assert.h>
#include "HW3.h"

//Stav Rones
//001201196

using namespace std;

//get decimal number from user input
void Dec2Bin::readDecNum(){
  string input;
  cout << "Enter a decimal number: ";
  cin >> input;
  decNum = atoi(input.c_str());
}

//print the binary equivalent recursively
void Dec2Bin::dec2bin_rcv(int d){
  if(d>=1) {
    dec2bin_rcv(d/2);
    cout << d%2;
  }
  else return;
}

//print the binary equivalent iteratively utilizing a stack
void Dec2Bin::dec2bin_itr(){
  if(decNum == 0) return;
  //initialize a stack of type int
  ArrayStack<int> stack;
  int temp = decNum;

  for(int i=0;i<log2(decNum)+1;i++){
    //push the reaminder to the stack for the length of the binary equivalent
    //which is calculated by log base 2 of decNum
    stack.push(temp%2);
    temp = temp/2;
  }

  while(!stack.isEmpty()){
    //while the stack is not empty, print and pop the top value
    cout << stack.peek();
    stack.pop();
  }
  cout << endl;
}

//pure recursion
int Problem3::fibonacci_rec(int n){
  if(n<=1) return n;
  return fibonacci_rec(n-1) + fibonacci_rec(n-2);
}

//recursion that uses a dynamic array to check which
//fibonacci numbers have already been calcualted
int Problem3::fibonacci_rec_dyn(int n){
  arr[n] = 0;
  if(n<=1) {arr[n] = n; return arr[n];}
  if(arr[n-1]==-1) fibonacci_rec_dyn(n-1);
  if(arr[n-2]==-1) fibonacci_rec_dyn(n-2);
  arr[n] = arr[n-1] + arr[n-2];
  return arr[n];
}


//stack implementation from class

template<class ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1){} // end default constructor

template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const{
  return top<0; } // end isEmpty

template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry){
  bool result= false;
  if(top< DEFAULT_CAPACITY-1){ // Does stack have room for newEntry?
    top++;
    items[top] = newEntry;
    result= true;
  } // end if
  return result;
}

template<class ItemType>
bool ArrayStack<ItemType>::pop(){
  bool result = false;
  if(!isEmpty()){
    top--;
    result = true;
  } // end if
  return result;
  } // end pop

template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const{
  assert(!isEmpty());
  return items[top];
}
