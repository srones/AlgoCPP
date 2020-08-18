//Stav Rones
//001201196
//HW01_main.cpp

//used this main to test my class functions
#include <iostream>
#include <fstream>
#include <string>
#include "HW01.h"

using namespace std;

int main() {

  while(true) {

    system("clear");
    printMenu();
    cout <<"Enter a number: ";
    char input [100];
    fgets(input,100,stdin);
    int choice = atoi(input);

    ifstream inf;
    inf.open("students.txt");

    if(choice==1) {
      system("clear");
      printMenu();

      cout << "> creating \"Person\" class \"Stav\"..." << endl;
      Person Stav;
      cout << "> calling Stav.readPersonInfo()..." << endl << endl;
      Stav.readPersonInfo(&inf);
      cout << "> calling Stav.printPersonInfo()..." << endl << endl;
      Stav.printPersonInfo();
      cout << "> calling Stav.personName..." << endl << endl;
      Stav.personName();
      cout << "> calling Stav.personAGE..." << endl << endl;
      Stav.personAGE();
    }

    if(choice==2) {
      cout << "> creating \"Student\" class \"student\"..." << endl;
      Student student;
      cout << "> calling student.readStudentInfo()..." << endl << endl;
      student.readStudentInfo(&inf);
      cout << "> calling student.printStudentInfo()..." << endl << endl;
      student.printStudentInfo();
      cout << "> calling student.studentGPA()..." << endl << endl;
      student.studentGPA();
    }

    if(choice==3){
      cout << "> creating \"Course\" class \"Algorithms\" with attributes:" << endl
           << "   ID: 123" << endl << "   title: Algo" << endl << "   credits: 4" << endl;
      Course Algorithms("123","Algo",4);
      cout << "> calling Algorithms.printCourseInfo()..." << endl << endl;
      Algorithms.printCourseInfo();
    }

    if(choice==4){
      // cout << "> Creating \"CourseSection\" class \"section1\" with attributes:" << endl
      //      << "   ID: 123" << endl
      //      << "   Title: Algo" << endl
      //      << "   credits: 4" << endl
      //      << "   Section Size: 5" << endl;
      CourseSection section1("123","Algo",4,10);
      section1.fillRosterInfo(&inf);
      section1.printSectionInfoByGPA();
    }

    if(choice==5) return 0;

    cout << "> Press any key to continue... ";
    fgets(input,100,stdin);
  }
}
