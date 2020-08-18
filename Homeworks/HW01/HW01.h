//Stav Rones
//001201196
//HW01.h

//Header file that declares classes and functions

#ifndef HW01_H
#define HW01_H
#include <iostream>
#include <string>

using namespace std;

//Person class
class Person {
    string fullname;
    string address;
    int age;
  public:
    void readPersonInfo();
    void printPersonInfo ();
    int personAGE();
    string personName();
};

//Student class, inherits from Person class
//public inheritence so baseclass public functions can be accessed
class Student : public Person {
    string ID;
    string major;
    float gpa;
  public:
    void readStudentInfo();
    void printStudentInfo();
    float studentGPA();
};

//Course class
class Course {
    string ID;
    string title;
    int credits;
  public:
    //non default constructor with args
    Course(string in1,string in2,int in3);
    void printCourseInfo();
};

//CourseSection class inherits from Course class
//public inheritence so baseclass public functions can be accessed
class CourseSection : public Course {
    int sectionSize;
    Student* roster;
  public:
    //non default constructor with args
    CourseSection(string in1,string in2,int in3, int in4);
    ~CourseSection(); //destructor
    void fillRosterInfo();
    void fillRosterInfo_test();
    void printSectionInfo();
    void printAverageGPA();
    void printYoungestStudent();
};

//helper function for program testing
void printMenu();

#endif
