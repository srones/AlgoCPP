#include <iostream>
#include <fstream>
#include <string>
#include "HW01.h"

int main() {
  int num, cr;
  string id, tl;
  ifstream inf;
  inf.open("c:\\temp\\section01.txt");
  //inf.open("section01.txt");
  if (inf.fail()) {
  cerr << "Error: Could not open input file\n";
  exit(1);
  }
  //activate the exception handling of inf stream
  inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  cout << "Course ID? "; cin >> id;
  cin.get(); //remove the leftover "new line" character from cin
  cout << "Course Title? ";
  getline(cin, tl);
  cout << "Course Credits? ";  cin >> cr;
  cin.get(); //remove the leftover "new line" character from cin
  cout << "How many students in the course section? "; cin >> num;
  cin.get(); //remove the leftover "new line" character from cin
  CourseSection sec(id, tl, cr, num); //define sec for CourseSection
  sec.fillRosterInfo(&inf); //ifstream cannot be passed by value
  inf.close();
  cout <<
  "Section info (course and students info) sorted by students' names:\n";
  sec.printSectionInfoByName();
  cout <<
  "\nSection info (course and students info) sorted by students' ages:\n";
  sec.printSectionInfoByAge();
  cout <<
  "\nSection info (course and students info) sorted by students' GPAs:\n";
  sec.printSectionInfoByGPA();
  return 0;
}
