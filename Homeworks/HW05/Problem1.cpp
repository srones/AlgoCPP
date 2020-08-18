#include <iostream>

using namespace std;

int h1(int key){
  int x = (key+5)*(key+5);
  x = x/16;
  x = x+key;
  x = x%11;
  return x;
}

int main(){

  int keys[] = {43,23,1,0,15,31,4,7,11,3,5,9};
  int size = 12;

  int hashTable[11]; for(int i=0;i<12;i++){hashTable[i]=-1;};
  int hashIndex,firstIndex;
  bool inserted = false;

  cout << "Probe Sequence:\n\n";
  for(int i=0;i<size;i++){              //look at every key
    cout << keys[i] << ": [";
    hashIndex = h1(keys[i]);
    firstIndex = hashIndex;
    inserted = false;


    while(!inserted){                     //start probing
      cout << hashIndex << ", ";
      if(hashTable[hashIndex] == -1) {
        hashTable[hashIndex] = keys[i];
        inserted = true;
      }
      else {
        hashIndex++;
        if(hashIndex == firstIndex){
          inserted = true;
          cout << "]\n" << keys[i] << " not inserted: hashTable full.\n";
        }
        if(hashIndex==11) hashIndex = 0;
      }
    }
    cout << "]\n\n";
  } //end for

  cout << "Final Hash Table: \n[";
  for(int i=0;i<11;i++){
    cout << hashTable[i] << ", ";
  }
  cout << "]\n";
}
