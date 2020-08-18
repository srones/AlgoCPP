#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <string>
#include <fstream>

extern int waitingQCapacity, eventsQCapacity;

using namespace std;

class BankCustomer{
public:
  int ID, ArrivalTime, ServiceStartTime, TransactionLength;
};

class Event{
public:
  char EventType;
  int CustID, ADTime;
  void printE(){
    cout << "[" << CustID << ", " << EventType << ", " << ADTime << "]\n";
  }
};

//EventsQ - list of events
class PQueue{
  Event* events;
  int QCapacity;
  int count;
  bool listInsert(Event ev);
  bool listDelete();
  Event listPeek();
  bool heapInsert(Event ev);
  bool heapDelete();
  Event heapPeek();
  void heapRebuild(int rootIndex);
public:
  PQueue(int c);
  ~PQueue();
  bool isEmpty();
  bool enqueue(Event ev);
  bool dequeue();
  Event peekFront();
  void printQ();
};

//waitingQ - list of integer IDs
class ArrayQueue{
  int QCapacity, front, back, count;
  int* IDs;
public:
  ArrayQueue(int c);
  ~ArrayQueue();
  bool isEmpty();
  bool enqueue(const int newID);
  bool dequeue();
  int peekFront();
  int queueLength();
  void printQ();
};

class BankTellerService {
  int BusyTeller,CustomersNum,maxTellers;
  ifstream inf;
  ofstream otf;
  ArrayQueue WaitingQ = ArrayQueue(waitingQCapacity);
  PQueue EventsQ = PQueue(eventsQCapacity);
  BankCustomer* Customers;
  int waitingQMax;
public:
  BankTellerService(string infS,string otfS,int tellers);
  ~BankTellerService();
  void readCustomersInfo();
  void serveCustomers();
  void getStatistics();
};

#endif
