#include <iostream>
#include <string>
#include <stdexcept>
#include "bank.h"

//global variables
#define maxCustomers 25
#define maxQSize 100
#define tellerNum 1 //number of tellers
int waitingQCapacity = 100;
int eventsQCapacity = 100;

using namespace std;

int main(){
    BankTellerService myBank("input.txt", "output.txt",tellerNum);
    myBank.readCustomersInfo();
    myBank.serveCustomers();
    myBank.getStatistics();
    return 0;
}


// ------------- PQueue --------------

void PQueue :: printQ(){
  cout << "[";
  for(int i=0;i<count;i++){
    cout << "["
    << events[i].CustID << ", "
    << events[i].EventType << ", "
    << events[i].ADTime << "],";
  }
  cout << "]\n";
}

PQueue :: PQueue(int c){
  QCapacity = c;
  events = new Event[c];
  int count = 0;
}

PQueue :: ~PQueue(){
  delete[] events;
}

bool PQueue :: listInsert(Event ev){

  //if empty, insert
  if(count==0){
    events[count]=ev;
    count++;
    return true;
  }

  //if not empty and not full:
  if(count<QCapacity){

    //if arrival:
    if(ev.ADTime=='A'){

      //shift until time is found and insert
      for(int i=count-1;i>-1;i--){
        if(ev.ADTime>events[i].ADTime) events[i+1]=events[i];
        else{
          events[i+1] = ev;
          count++;
          return true;
        }
      }
      events[0]=ev;
      count++;
      return true;
    }

    //if departure:
    else{
      for(int i=count-1;i>-1;i--){
        if(ev.ADTime>events[i].ADTime && events[i].EventType == 'A') {
          events[i+1]=events[i];
        }
        else{
          events[i+1] = ev;
          count++;
          return true;
        }
      }
      events[0]=ev;
      count++;
      return true;
    }

  }

  //over capacity
  return false;
}

bool PQueue :: listDelete(){
  if(count>0){
    count--;
    return true;
  }
  return false;
}

Event PQueue :: listPeek(){
  assert(!isEmpty());
  return events[count-1];
}

bool PQueue :: heapInsert(Event ev){

  //if heap is full:
  if(count>=QCapacity) return false;

  //place new events at "bottom" of tree
  events[count] = ev;
  int newDataIndex = count;
  bool inPlace = false;
  int parentIndex;

  while((newDataIndex>0)&& !inPlace){
    parentIndex = (newDataIndex-1)/2;

    //if time is sooner than parent, bubble up
    if(events[newDataIndex].ADTime < events[parentIndex].ADTime){
      swap(events[newDataIndex],events[parentIndex]);
      newDataIndex = parentIndex;
    }

    //if time is greater to or equal than parent:
    else{
      // if time greater, then in place
      if(events[newDataIndex].ADTime > events[parentIndex].ADTime) inPlace = true;
      // if time == and arrival, then in place
      if(events[newDataIndex].EventType=='A') inPlace = true;
      // if time == and departure, bubble up
      else{
        while((newDataIndex>0)&& !inPlace){
          //currTime == parentTime
          if(events[parentIndex].ADTime==events[newDataIndex].ADTime){
            swap(events[newDataIndex],events[parentIndex]);
            newDataIndex = parentIndex;
          }
          else inPlace = true;
        }
      }
    }
  }
  count++;
  return true;
}

bool PQueue :: heapDelete(){
  events[0]=events[count-1];
  count--;
  heapRebuild(0);
  return true;
}

void PQueue :: heapRebuild(int rootIndex){
  int toSwap,rightChildIndex,leftChildIndex;
  bool swapFlag = false;

  // if not a leaf:
  if(rootIndex<count/2){

    leftChildIndex = (2*rootIndex)+1;
    toSwap = leftChildIndex;
    rightChildIndex = 2*rootIndex+2;

    //has only left child
    if(rightChildIndex>=count){
        //root is greater than child: swap
        if(events[rootIndex].ADTime > events[leftChildIndex].ADTime) swapFlag = true;
        // root is equal:
        if(events[rootIndex].ADTime == events[leftChildIndex].ADTime){
          // root is arrival: swap
          if(events[rootIndex].EventType=='A' && events[leftChildIndex].EventType=='D') swapFlag = true;
        }
    }

    //has a right child
    if(rightChildIndex<count){
      //rightChild time less than left: toSwap = right
      if(events[rightChildIndex].ADTime<events[leftChildIndex].ADTime) toSwap=rightChildIndex;
      // if both children are equal times:
      if(events[leftChildIndex].ADTime == events[rightChildIndex].ADTime){
        // right is departure: swap right
        if(events[rightChildIndex].EventType=='D') toSwap = rightChildIndex;
      }
      if(events[rootIndex].ADTime>=toSwap) swapFlag = true;
    }

    if(swapFlag){
      swap(events[rootIndex],events[toSwap]);
      heapRebuild(toSwap);
    }
  }
}

Event PQueue :: heapPeek(){
  return events[0];
}

bool PQueue :: isEmpty(){
  return count==0;
}

bool PQueue :: enqueue(Event ev){
  return heapInsert(ev);
}

bool PQueue :: dequeue(){
  return heapDelete();
}

Event PQueue :: peekFront(){
  return heapPeek();
}

// ------------- AQueue --------------

ArrayQueue :: ArrayQueue (int c){
  QCapacity = c;
  IDs = new int[c];
  front = 0;
  back = c-1;
  count = 0;
}

ArrayQueue :: ~ArrayQueue (){
  delete[] IDs;
}

bool ArrayQueue :: isEmpty(){
  return count==0;
}

bool ArrayQueue :: enqueue(int newID){
  if(count<QCapacity){
    back = (back+1)%QCapacity;
    IDs[back] = newID;
    count++;

    return true;
  }
  return false;
}

bool ArrayQueue :: dequeue(){
  if(!isEmpty()){
    front = front + 1 % QCapacity;
    count--;
    return true;
  }
  return false;
}

int ArrayQueue :: peekFront(){
  assert(!isEmpty());
  return IDs[front];
}

int ArrayQueue :: queueLength(){
  return count;
}

void ArrayQueue :: printQ(){
  cout << "[";
  for(int i=front;i<count;i++){
    cout << "[" << IDs[i] << "],";
  }
  cout << "]\n";
}

// ------------- BankTellerService --------------

BankTellerService :: BankTellerService(string infS, string otfS,int tellers){
  Customers = new BankCustomer[maxCustomers];
  maxTellers = tellers;
  BusyTeller = 0;

  inf.open(infS);
  if(inf.fail()) { cerr << "Error opening the input file\n"; exit(1); }
  inf.exceptions(ifstream::failbit | ifstream::badbit);
  otf.open(otfS);
  if(otf.fail()) { cerr << "Error opening the output file\n"; exit(1); }
}

BankTellerService :: ~BankTellerService() {
  delete[] Customers;
  inf.close();
  otf.close();
}

void BankTellerService :: readCustomersInfo(){
  int list[maxCustomers*3];
  int count = 0;
  int x;

  //read from text file
  while(count<maxCustomers){
    try{ inf>>x; }
    catch(ifstream::failure e){ break; }
    list[count++]=x;
  }

  CustomersNum = count/2;

  //convert temp list into Customer list
  for(int i=0;i<(count/2);i++){
    BankCustomer* customer = new BankCustomer();
    customer->ID = i;
    customer->ArrivalTime = list[i*2];
    customer->TransactionLength = list[(i*2)+1];
    Customers[i] = *customer;
  }

  //create arrival events and store in priority queue
   for(int i=0;i<(count/2);i++){
     Event* event = new Event();
     event->EventType = 'A';
     event->CustID = Customers[i].ID;
     event->ADTime = Customers[i].ArrivalTime;
     if(!EventsQ.enqueue(*event)) cout << "Event not added to EventsQ";
   }

   //EventsQ.printQ();
   // while(!EventsQ.isEmpty()){
   //   EventsQ.dequeue();
   //   EventsQ.printQ();
   // }
}

void BankTellerService :: serveCustomers(){
    int departureTime,customerID,transactionTime,serviceTime,waitingQ;
    waitingQMax = 0;

    otf << maxTellers << " tellers:\n\n";

    //while the event queue is not empty:
    while(!EventsQ.isEmpty()){
      Event currentEvent = EventsQ.peekFront();

      //if event is an arrival:
      if(currentEvent.EventType == 'A'){

        customerID = currentEvent.CustID;
        otf << "Customer " << customerID << " arrived at time <-- " << currentEvent.ADTime << endl;
        // << " with transactionTime = " << Customers[customerID].TransactionLength << ".\n";

        //if teller is busy, add customer to WaitingQ
        if(BusyTeller >= maxTellers){
          // otf << "  - Teller is busy, send customer " << currentEvent.CustID << " to waiting line\n";
          WaitingQ.enqueue(currentEvent.CustID);
          waitingQ = WaitingQ.queueLength();
          if(waitingQ>waitingQMax) waitingQMax = waitingQ;
          otf << "Customer " << currentEvent.CustID << " added to waitingQ\n";

          EventsQ.dequeue();
        }

        //if teller is not busy:
        else{

          //if waitingQ is empty, serve the customer
          if(WaitingQ.isEmpty()){
            BusyTeller++;

            Event* departureEvent = new Event();
            customerID = currentEvent.CustID;
            transactionTime = Customers[customerID].TransactionLength;
            departureTime = currentEvent.ADTime + transactionTime;
            departureEvent->EventType = 'D';
            departureEvent->CustID = currentEvent.CustID;
            departureEvent->ADTime = departureTime;

            Customers[customerID].ServiceStartTime = currentEvent.ADTime;

            // otf << "  - Now serving customer " << currentEvent.CustID
            // << " at time " << currentEvent.ADTime
            // << ", whose transactionTime = " << transactionTime
            // << ". Departure event added at time " << departureTime << ".\n";

            EventsQ.enqueue(*departureEvent);
            EventsQ.dequeue();
          }

          //if waitingQ not empty, serve the customer in the waitingQ
          // **
          else{
            cout << "test";
            BusyTeller++;

            Event* departureEvent = new Event();
            customerID = WaitingQ.peekFront();
            serviceTime = Customers[customerID].ServiceStartTime;
            transactionTime = Customers[customerID].TransactionLength;
            departureTime = serviceTime + transactionTime;
            departureEvent->EventType = 'D';
            departureEvent->CustID = customerID;
            departureEvent->ADTime = departureTime;

            // otf << "  - Now serving customer " << customerID
            // << " at time " << serviceTime
            // << ", whose transactionTime = " << transactionTime
            // << ". Departure event added at time " << departureTime << ".\n";

            EventsQ.enqueue(*departureEvent);
            WaitingQ.dequeue();
            otf << "Customer " << customerID << " removed from waitingQ\n";
          }
        }
      }

      //if departure:
      else{
        //WaitingQ not empty
        if(!WaitingQ.isEmpty()){

          //update start time of WaitingQ
          customerID = WaitingQ.peekFront();
          Customers[customerID].ServiceStartTime = currentEvent.ADTime;
          // otf << " - Customer " << WaitingQ.peekFront() << " serviceTime changed to " << currentEvent.ADTime << ".\n";

          //get rid of departure event
          otf << "Customer " << currentEvent.CustID
          << " departed at time --> " << currentEvent.ADTime << ".\n";
          BusyTeller--;
          EventsQ.dequeue();
          // EventsQ.printQ();

          //serve the WaitingQ
          BusyTeller++;

          Event* departureEvent = new Event();
          customerID = WaitingQ.peekFront();
          serviceTime = Customers[customerID].ServiceStartTime;
          transactionTime = Customers[customerID].TransactionLength;
          departureTime = serviceTime + transactionTime;
          departureEvent->EventType = 'D';
          departureEvent->CustID = customerID;
          departureEvent->ADTime = departureTime;

          // otf << "  - Now serving customer " << customerID
          // << " at time " << serviceTime
          // << ", whose transactionTime = " << transactionTime
          // << ". Departure event added at time " << departureTime << ".\n";

          //add the departure event and dequeue the waitingQ
          EventsQ.enqueue(*departureEvent);
          WaitingQ.dequeue();
          otf << "Customer " << customerID << " removed from waitingQ\n";
        }

        // waiting line is empty and there is a departure event
        else{
          otf << "Customer " << currentEvent.CustID
          << " departed at time --> " << currentEvent.ADTime << ".\n";
          BusyTeller--;
          EventsQ.dequeue();
        }
      }
    }
    otf << "\n";
    //end while
}

void BankTellerService :: getStatistics(){

  float waitTime;
  float avgWaitTime = 0;
  int maxWaitTime = 0;

  for(int i=0;i<CustomersNum;i++){
    waitTime = Customers[i].ServiceStartTime - Customers[i].ArrivalTime;
    if(waitTime > maxWaitTime) maxWaitTime = waitTime;
    avgWaitTime += waitTime;
  }
  avgWaitTime = avgWaitTime / CustomersNum;

  otf << "Final Statistics:\n"
  << "Total number of customers processed =  " << CustomersNum << endl
  << "Average waiting time =  " << avgWaitTime << endl
  << "Maximum waiting time =  " << maxWaitTime << endl
  << "Maximum waiting queue length = " << waitingQMax << endl;

}
