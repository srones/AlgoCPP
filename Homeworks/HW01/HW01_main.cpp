#include <iostream>
#include <string>
#include "HW01.h" //include header file

using namespace std;

int main() {
  int num, cr;
  string id, tl;

  cout << "Course ID? ";
  cin >> id;

  cout << "Course Title? ";
  cin.get();  //remove the leftover "new line" character from cin
  getline(cin, tl); //allows for spaces in the title but first clear the input buffer.

  cout << "Course Credits? ";
  cin >> cr;

  cout << "How many students in the course section? ";
  cin >> num;
  cin.get();  //remove the leftover "new line" character from cin

  CourseSection sec(id, tl, cr, num);

  cout << "Input the info of all students in the section:\n";
  sec.fillRosterInfo();

  cout << "The following is the section info (course and students info):\n";

  sec.printSectionInfo();
  cout << "\nThe average GPA of the students in the section = ";

  sec.printAverageGPA();
  cout << "\nThe youngest student in the class:\n";

  sec.printYoungestStudent();
  return 0;
}
