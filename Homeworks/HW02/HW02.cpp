//Stav Rones
//001201196
//HW02.cpp
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cstring>
#include <locale>
#include <algorithm> //for transform::toupper
#include "HW01.h"

using namespace std;

  //function used in my testMain to test all the classes
void printMenu(){
    cout << "1. Test \"Person\" class" << endl
         << "2. Test \"Student\" class" << endl
         << "3. Test \"Course\" class" << endl
         << "4. Test \"CourseSection\" class" << endl
         << "5. Exit" << endl << "-------------" << endl << endl;
}

//Populates the attributes of the person class by reading from file
void Person::readPersonInfo(ifstream* sf) {
    string temp;
    getline(*sf,fullname);
    getline(*sf,address);
    getline(*sf,temp);
    age = atoi(temp.c_str());
}

//prints the person attributes to stdout with formatting
void Person::printPersonInfo () {
  cout << left
  << setw(20) << fullname
  << setw(20) << address
  << setw(5) << age;
}

//returns the person's age attribute
int Person::personAGE() {
  return age;
}

//returns the person's fullname attribute
string Person::personName() {
  return fullname;
}

//populate the student attributes via reading from file
void Student::readStudentInfo(ifstream* sf) {
  readPersonInfo(sf);
  string temp;
  getline(*sf,ID);
  getline(*sf,major);
  getline(*sf,temp);
  gpa = atof(temp.c_str());
}

//print the student object's private attributesw with formatting
void Student::printStudentInfo () {
  printPersonInfo(); //first call superclass function to print personal info
  cout << left
   << setw(10) << ID
   << setw(10) << major
   << setw(10) << gpa
   << endl;
  cout << endl;
}

//returns the private float gpa attrubute of the student
float Student::studentGPA() {
  return gpa;
}

//Constructor for the Course object that requires 3 arguments
Course::Course(string in1,string in2,int in3) {
  //populates the private attributes of Course with the constructor arguments
  ID = in1;
  title = in2;
  credits = in3;
}

//Prints the private attributes of the course object
void Course::printCourseInfo() {
  cout << "This section has the following info:" << endl
       << "   ID: " << ID << endl
       << "   Title: " << title << endl
       << "   Credits: " << credits <<endl;
}

//Constructor for the CourseSectino object with 4 args. 3 of these args are
//used to construct the superclass it inherits from
CourseSection::CourseSection(string in1,string in2,int in3, int in4) : Course(in1,in2,in3) {
  sectionSize = in4;
  roster = new Student[sectionSize]; //store student objects in roster
  sortedNames = new Student*[sectionSize]; //create array of student pointers
  sortedAges = new Student*[sectionSize]; //this is done to conserve memory
  sortedGPAs = new Student*[sectionSize]; //so only pointers are needed
}

//popylate roster with students by repeadedly calling readStudentInfo
//roster stores the student object, the other arrays store pointers
void CourseSection::fillRosterInfo(ifstream *rf) {
  for(int i = 0; i < sectionSize; i++) {
    Student* student = new Student();
    student->readStudentInfo(rf);
    roster[i] = *student;
    sortedNames[i] = student;
    sortedAges[i] = student;
    sortedGPAs[i] = student;
  }
  //call the functions to sort the arrays of student object pointers
  sortNames();
  sortAges();
  sortGPAs();
}

//use insertion sort to sort sortedNames array alphabetically by student name
void CourseSection::sortNames(){
  bool condition;
  string str1,str2;
  int i,j;
  Student* key;

  for(i = 1; i < sectionSize; i++) {
    j = i-1;
    key = sortedNames[i];

    while(j>=0){
      str1 = key->personName();
      str2 = sortedNames[j]->personName();
      //convert to uppercase
      transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
      transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
      condition = str1 < str2;
      if(!condition) break;
      sortedNames[j+1] = sortedNames[j];
      j--;
    }
    sortedNames[j+1] = key;
  }
}

//use insertion sort to sort sortedAges array by student age
void CourseSection::sortAges(){
  bool condition;
  int i,j,int1,int2;
  Student* key;

  for(i = 1; i < sectionSize; i++) {
    j = i-1;
    key = sortedAges[i];
    while(j>=0){
      int1 = key->personAGE();
      int2 = sortedAges[j]->personAGE();
      condition = int1 < int2;
      if(!condition) break;
      sortedAges[j+1] = sortedAges[j];
      j--;
    }
    sortedAges[j+1] = key;
  }
}

//use insertion sort to sort sortedGPAs array by student GPA
void CourseSection::sortGPAs(){
  bool condition;
  int i,j;
  float fl1,fl2;
  Student* key;

  for(i = 1; i < sectionSize; i++) {
    j = i-1;
    key = sortedGPAs[i];
    while(j>=0){
      fl1 = key->studentGPA();
      fl2 = sortedGPAs[j]->studentGPA();
      condition = fl1 < fl2;
      if(!condition) break;
      sortedGPAs[j+1] = sortedGPAs[j];
      j--;
    }
    sortedGPAs[j+1] = key;
  }
}

//print the courseSection students alphabetically with formatting
void CourseSection::printSectionInfoByName(){
  printTitle();
  for(int i = 0; i < sectionSize; i++) {
    cout << left << setw(5) << i;
    sortedNames[i]->printStudentInfo();
  }
}

//print the courseSection students by age with formatting
void CourseSection::printSectionInfoByAge(){
  printTitle();
  for(int i = 0; i < sectionSize; i++) {
    cout << left << setw(5) << i;
    sortedAges[i]->printStudentInfo();
  }
}

//print the courseSection students by GPA with formatting
void CourseSection::printSectionInfoByGPA(){
  printTitle();
  for(int i = 0; i < sectionSize; i++) {
    cout << left << setw(5) << i;
    sortedGPAs[i]->printStudentInfo();
  }
}

//Destructor that deletes the dynamically created space for the Student array
CourseSection::~CourseSection() {
  delete[] roster;
  delete[] sortedNames;
  delete[] sortedAges;
  delete[] sortedGPAs;
}

//helper function to print the menu for courseSection printing
void printTitle(){
  cout << left
   << setw(5) << "Seq"
   << setw(20) << "Name"
   << setw(20) << "Address"
   << setw(5) << "Age"
   << setw(10) << "ID"
   << setw(10) << "Major"
   << setw(10) << "GPA"
   << endl
   << setw(5) << "==="
   << setw(20) << "==="
   << setw(20) << "==="
   << setw(5) << "==="
   << setw(10) << "==="
   << setw(10) << "==="
   << setw(10) << "==="
   << endl;
}
