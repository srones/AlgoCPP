#ifndef HW03_H
#define HW03_H
#include <iostream>
#include <string>

using namespace std;

extern int moves,comps;

void selectionSort(int arr[],int size){
  moves=0;
  comps=0;

  int largest;
  int largestIndex;
  for(int i=size-1;i>=0;i--){
    largest = 0;
    largestIndex = 0;

    for(int j=0;j<=i;j++){
      if(arr[j]>largest) {
        largest=arr[j];
        largestIndex=j;
      }
      comps++;
    }
    if(largestIndex!=i){
      swap(arr[largestIndex],arr[i]);
      moves+=3;
    }
  }
}

void bubbleSort(int arr[],int size){
  moves = 0;
  comps = 0;

  int pass = 1;
  bool sorted = false;

  while(!sorted && pass<size){
    sorted = true;
    for(int i=0;i<size-pass;i++){
      if(arr[i]>arr[i+1]){
        swap(arr[i],arr[i+1]);
        sorted = false;
        moves+=3;
      }
      comps++;
    }
    pass++;
  }
}

void insertionSort(int arr[],int size){
  bool inserted;
  int copy,j;

  for(int i=1;i<size;i++){
    inserted = false;
    copy = arr[i];
    j = i-1;

    while(j>=0 && !inserted){
      if(copy<arr[j]){
        arr[j+1]=arr[j];
        moves++;
      }
      else{
        arr[j+1]=copy;
        inserted = true;
        if(j+1 != i) moves++;
      }
      comps++;
      j--;
    }
    if(j<0 && !inserted){
      arr[0]=copy;
      moves++;
    }
  }
}

void merge(int A[],int first,int mid,int last){

  int B[1000];

  int first1 = first;
  int last1 = mid;
  int first2 = mid+1;
  int last2 = last;

  //merge two lists into tempArr
  int index = first1;
  while((first1 <= last1) && (first2 <= last2)){
    if(A[index] <= A[first1]){
      B[index] = A[first1];
      moves++;
      first1++;
    }
    else {
      B[index] = A[first2];
      moves++;
      first1++;
    }
    comps++;
    index++;
  }

  //if one lists used up, put in rest of other list
  while(first1<=last1){
    B[index]=A[first1];
    moves++;
    first1++;
    index++;
  }
  while(first2<=last){
    B[index]=A[first2]; moves++;
    first2++;
    index++;
  }

  //copy tempArr back into inputArr
  for(index = first; index <= last; index++){
    A[index] = B[index]; moves++;
  }
}

void mergeSort_rec(int A[], int first, int last){
  if(first<last){
    int mid = first + (last-first)/2;
    mergeSort_rec(A,first,mid);
    mergeSort_rec(A,mid+1,last);
    merge(A,first,mid,last);
  }
}

void mergeSort(int arr[],int size){
  moves = 0;
  comps = 0;
  mergeSort_rec(arr,0,size-1);
}

int sortFirstMiddleLast(int arr[],int first,int last){
  int mid = first + (last-first)/2;
  if(arr[first]>arr[mid]) {
    swap(arr[first],arr[mid]);
    moves+=3;
  }
  if(arr[mid]>arr[last]){
    swap(arr[mid],arr[last]);
    moves+=3;
  }
  if(arr[first]>arr[mid]){
    swap(arr[first],arr[mid]);
    moves+=3;
  }
  comps+=3;

  return mid;
}

int partition(int arr[],int first,int last){
  int pivotIndex = sortFirstMiddleLast(arr,first,last);
  swap(arr[pivotIndex],arr[last-1]); moves+=3;
  pivotIndex = last-1;

  int pivot = arr[pivotIndex];
  int i = first+1;
  int j = last-2;
  bool done = false;

  while(!done){
    while(arr[i]<pivot){
      i++; comps++;
    }
    comps++;
    while(arr[j]>pivot){
      j--; comps++;
    }
    comps++;

    if(i < j){
      swap(arr[i],arr[j]); moves+=3;
      i++; j--;
    }
    else done = true;
  }

  swap(arr[pivotIndex],arr[i]); moves+=3;
  return i;

}

void quickSort_rec(int arr[],int first,int last){
  int size = last-first+1;
  if(size<10){
    insertionSort(arr+first,size);
  }
  else{
    int pivotIndex = partition(arr, first, last);
    quickSort_rec(arr,first,pivotIndex-1);
    quickSort_rec(arr,pivotIndex+1,last);
  }
}

void quickSort(int arr[],int size){
  moves = 0;
  comps = 0;
  quickSort_rec(arr,0,size-1);
}

void heapRebuild(int rootIndex, int items[], int itemCount){
  int largerChildIndex;
  if(rootIndex<itemCount/2){
    largerChildIndex = (2*rootIndex)+1;
    int rightChildIndex = 2*rootIndex+2;
    if(rightChildIndex<itemCount){
        if(items[rightChildIndex]>items[largerChildIndex]){
          largerChildIndex = 2*rootIndex+2;
          comps++;
        }

    }
    if(items[rootIndex]<items[largerChildIndex]){
      comps++;
      swap(items[rootIndex],items[largerChildIndex]);
      moves+=3;
      heapRebuild(largerChildIndex,items,itemCount);
    }
  }
}

void heapCreate(int items[],int itemCount){
  for(int index=((itemCount/2)-1);index>=0;index--){
    heapRebuild(index,items,itemCount);
  }
}

void heapSort(int arr[],int size){
  moves=0;
  comps=0;
  heapCreate(arr,size);
  while(size > 1){
    swap(arr[0],arr[size-1]);
    moves+=3;
    size--;
    heapRebuild(0,arr,size);
  }
}

#endif
