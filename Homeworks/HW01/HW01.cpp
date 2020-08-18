//Stav Rones
//001201196
//HW01.cpp

#include <iostream>
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

  //Populates the attributes of the person class by prompting user input
  void Person::readPersonInfo() {
    char temp [100]; //input buffer
    int flag = 0; //flag for making sure age input is valid

    //populate fullname field
    cout << "   Full name:  ";
    fgets(temp,100,stdin);
    fullname = temp;

    //populate address field
    cout << "   Address: ";
    fgets(temp,100,stdin);
    address = temp;

    //make sure input is a valid int
    while(flag==0) {
      cout << "   Age: ";
      fgets(temp,100,stdin);
      age = atoi(temp); //convert input buffer to int
      if(age == 0) cout << "Please enter a valid integer age" << endl;
      else flag = 1;
    }
  }

  //prints the person attributes to stdout
  void Person::printPersonInfo () {
    cout << fullname
         << "   Address: " << address
         << "   Age: " << age << endl;
  }

  //returns the person's age attribute
  int Person::personAGE() {
    return age;
  }

  //returns the person's fullname attribute
  string Person::personName() {
    return fullname;
  }

  //populate the student attributes via prompting user
  void Student::readStudentInfo() {
    readPersonInfo(); //use the already existing function to prompt for personal information

    char temp [100]; //input buffer
    int flag = 0; //to make sure GPA is valid input

    cout << "Please enter the following academic information: " << endl;
    //populate ID attribute
    cout << "   ID:  ";
    fgets(temp,100,stdin);
    ID = temp;

    //populate major attribute
    cout << "   Major: ";
    fgets(temp,100,stdin);
    major = temp;

    //check for valid GPA input and populate
    while(flag==0) {
      cout << "   GPA: ";
      fgets(temp,100,stdin);
      gpa = atof(temp); //convert input buffer to float
      if(gpa==0) cout << "Please enter a valid float gpa" << endl;
      else flag = 1;
    }
    cout << endl;
  }

  //print the student object's private attributes
  void Student::printStudentInfo () {
    printPersonInfo(); //first call superclass function to print personal info
    cout << "   ID: " << ID
         << "   Major: " << major
         << "   GPA: " << gpa << endl << endl;
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
    roster = new Student[sectionSize]; //dynamically create the space for an
    //array of type Student with the given section size
  }

  //create student objects via user input for each student in the section,
  //given by section size
  void CourseSection::fillRosterInfo() {
    bool condition;
    string str1,str2;
    int i = 1;

    //dynamically create a new Student object to hold the student that
    //will act as the key for insertion sort
    Student* key = new Student();
    cout << "Student " << i << ": " << endl;
    key->readStudentInfo(); //populate student attributes with user input

    roster[0] = *key; //put the student in the first position of the list

    //insertion sort algorithm
    for(int j = 1; j < sectionSize; j++) {
      cout << "Student " << j+1 << ": " <<endl; //allow user to keep track of
      //how many studets they have created
      key = new Student(); //create new student
      key->readStudentInfo(); //populate student attributes with user input
      i = j-1;

      while(i>=0) {
        //store the two names to be compared
        str1 = roster[i].personName();
        str2 = key->personName();
        //convert them to uppercase before comparing to negate effect of case
        transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
        transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
        //compute the condition for the loop within insertion sort
        condition = str1 > str2;

        //determine where the key student should be inserted and
        //move the previous sorted list forward in the array
        //until the key is inserted correctly
        if(!condition) break;
        roster[i+1] = roster[i];
        i--;
      }
      //insert the key student into the array
      roster[i+1] = *key;
    }
    //delete the dynamically allocated key Student
    delete key;
  }

  //Display course info and roster
  void CourseSection::printSectionInfo() {
    printCourseInfo(); //previously defined function
    cout << "   Section size: " << sectionSize <<endl<<endl
         << "Students (alphabetical order): " <<endl<<endl;
      //loop through roster and display each student's information
       for(int i=0;i<sectionSize;i++) {
         roster[i].printStudentInfo();
       }
  }

  //Calculate and display the average GPA of the course section
  void CourseSection::printAverageGPA() {
    float GPAavg = 0;
    if(roster != NULL) { //make sure course is not empty
      //loop through roster and create sum of all GPAs
      for(int i=0;i<sectionSize;i++) {
        GPAavg += roster[i].studentGPA();
      //devide sum by n
    }
        GPAavg = GPAavg / sectionSize;
        cout << GPAavg <<endl<<endl; //display
    }
  }

  //determines and displays the youngest student in course section information
  void CourseSection::printYoungestStudent() {
    if(roster != NULL) { //make sure roster exists
      //set the first student to be the youngest
      int AGEmin = roster[0].personAGE();
      Student* youngest = &roster[0]; //pointer to keep track of youngest student

      //loop roster and check if each student's age is smaller than the min
      //if so, set that student to the be the youngest
      for(int i=1;i<sectionSize;i++) {
        if(roster[i].personAGE()<AGEmin) {
          AGEmin = roster[i].personAGE();
          youngest = &roster[i];
        }
      }
      youngest->printStudentInfo(); //display
      cout <<endl<<endl;
    }
  }

  //Destructor that deletes the dynamically created space for the Student array
  CourseSection::~CourseSection() {
    delete[] roster;
  }
