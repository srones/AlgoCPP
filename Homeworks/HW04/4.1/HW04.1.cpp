#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include "sort.h"

using namespace std;

//Global variables
int moves,comps;

//-------------- Helper Functions --------------

void reinitialize(int BST[],int AVG[],int WST[],int tBST[],int tAVG[],int tWST[]){
  for(int i=0;i<1000;i++){
    tBST[i]= BST[i];
    tWST[i]= WST[i];
    tAVG[i]= AVG[i];
  }
  moves = 0;
  comps = 0;
}

//pass arrays by reference and modify them
void generateArrays(int BST[],int AVG[], int WST[]){
  srand(time(NULL));
  for(int i=0;i<1000;i++){
    BST[i]=i;
    WST[i]=999-i;
    AVG[i]=rand() % 100000;
  }
}

void writeFile(bool newFile, string sortType){
  ofstream outf;
  if(newFile) outf.open("sort.txt");
  else outf.open("sort.txt", ios::app);

  if (outf.fail()) {
    cerr << "Error: Could not open output file\n";
    exit(1);
  }
  outf << sortType << endl << "Moves: " << moves << "\nComps: " << comps << endl << endl;
  outf.close();
}

bool verifySort(int arr[]){
  for(int i=0;i<999;i++){
    if(arr[i+1]<arr[i]) return false;
  }
  return true;
}

void printArrays(int tBST[],int tAVG[],int tWST[]){
  cout << "tBST: [";
  for(int i=0;i<10;i++){
     cout<<tBST[i]<<", ";
  }
  for(int i=995;i<1000;i++){
     cout<<tBST[i]<<", ";
  }

  cout << "]\ntAVG: [";
  for(int i=0;i<10;i++){
     cout<<tAVG[i]<<", ";
  }
  for(int i=995;i<1000;i++){
     cout<<tAVG[i]<<", ";
  }

  cout << "]\ntWST: [";
  for(int i=0;i<10;i++){
     cout<<tWST[i]<<", ";
  }
  for(int i=995;i<1000;i++){
     cout<<tWST[i]<<", ";
  }
  cout << "]\n";
}

//-------------- Main --------------

int main() {

  //initialize arrays
  int BST[1000];
  int AVG[1000];
  int WST[1000];
  int tBST[1000];
  int tAVG[1000];
  int tWST[1000];

  //generate arrays
  generateArrays(BST,AVG,WST);

  //Selection sort:
  reinitialize(BST,AVG,WST,tBST,tAVG,tWST);

  selectionSort(tBST,1000);
  writeFile(true,"Selection Sort Best Case: ");
  selectionSort(tAVG,1000);
  writeFile(false,"Selection Sort Average Case: ");
  selectionSort(tWST,1000);
  writeFile(false,"Selection Sort Worst Case: ");

  if(!verifySort(tBST) || !verifySort(tAVG) || !verifySort(tWST)) cout << "Error with Selection Sort" << endl;

  // Bubble sort:
  reinitialize(BST,AVG,WST,tBST,tAVG,tWST);

  bubbleSort(tBST,1000);
  writeFile(false,"Bubble Sort Best Case: ");
  bubbleSort(tAVG,1000);
  writeFile(false,"Bubble Sort Average Case: ");
  bubbleSort(tWST,1000);
  writeFile(false,"Bubble Sort Worst Case: ");

  if(!verifySort(tBST) || !verifySort(tAVG) || !verifySort(tWST)) cout << "Error with bubble Sort" << endl;


  // Insertion sort:
  reinitialize(BST,AVG,WST,tBST,tAVG,tWST); moves = 0; comps = 0;

  insertionSort(tBST,1000);
  writeFile(false,"Insertion Sort Best Case: "); moves = 0; comps = 0;
  insertionSort(tAVG,1000);
  writeFile(false,"Insertion Sort Average Case: "); moves = 0; comps = 0;
  insertionSort(tWST,1000);
  writeFile(false,"Insertion Sort Worst Case: "); moves = 0; comps = 0;

  if(!verifySort(tBST) || !verifySort(tAVG) || !verifySort(tWST)) cout << "Error with insertionSort Sort" << endl;

  //Merge sort:
  reinitialize(BST,AVG,WST,tBST,tAVG,tWST);

  printArrays(tBST,tAVG,tWST);

  mergeSort(tBST,1000);
  writeFile(false,"Merge Sort Best Case: ");
  mergeSort(tAVG,1000);
  writeFile(false,"Merge Sort Average Case: ");
  mergeSort(tWST,1000);
  writeFile(false,"Merge Sort Worst Case: ");

  printArrays(tBST,tAVG,tWST);

  if(!verifySort(tBST) || !verifySort(tAVG) || !verifySort(tWST)) cout << "Error with merge Sort" << endl;

  // Quick sort:
  reinitialize(BST,AVG,WST,tBST,tAVG,tWST);

  quickSort(tBST,1000);
  writeFile(false,"Quick Sort Best Case: ");
  quickSort(tAVG,1000);
  writeFile(false,"Quick Sort Average Case: ");
  quickSort(tWST,1000);
  writeFile(false,"Quick Sort Worst Case: ");

  if(!verifySort(tBST) || !verifySort(tAVG) || !verifySort(tWST)) cout << "Error with Quick Sort" << endl;
}
