#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Course { string name;
   string number;
   int creditHours;
   char grade;

public:
   void getData(ifstream &inputFile) {
       inputFile >> name >> number >> creditHours >> grade;}

   void displayData() {
       cout << "Course No: " << number << endl;
       cout << "Course Name: " << name << endl;
       cout << "Credits: " << creditHours << endl;
       cout << "Grade: " << grade << endl;
   }

   float getGPA() {
       int points;
       switch (grade) {
           case 'A':
               points = 4;
               break;
           case 'B':
               points = 3;
               break;
           case 'C':
               points = 2;
               break;
           case 'D':
               points = 1;
               break;
           default:
               points = 0;
       }
       return points;
   }

   // Getter for credit hours
   int getCreditHours() const {
       return creditHours;
   }

   // Setter for credit hours
   void setCreditHours(int hours) {
       creditHours = hours;
   }
};
 // ... (rest of the code is the same)


class Student { string name;
   int id;
   bool isTuitionPaid;
   int numberOfCourses;
   Course courses[100]; // assuming a maximum of 100 courses

public:
   Student(string name, int id, bool isTuitionPaid, int numberOfCourses)
       : name(name), id(id), isTuitionPaid(isTuitionPaid), numberOfCourses(numberOfCourses) {}

   void getData(ifstream &inputFile) {
       for (int i = 0; i < numberOfCourses; i++) {
           courses[i].getData(inputFile);
       }
   }

   void displayData() {
       cout << "Student Name: " << name << endl;
       cout << "Student ID: " << id << endl;
       cout << "Number of courses enrolled: " << numberOfCourses << endl;

       for (int i = 0; i < numberOfCourses; i++) {
           courses[i].displayData();
       }

       int totalCredits = 0;
       float totalGPA = 0;
       for (int i = 0; i < numberOfCourses; i++) {
           totalCredits += courses[i].getCreditHours();
           totalGPA += courses[i].getGPA();
       }
       cout << "Total number of credits: " << totalCredits << endl;
       cout << "Mid-Semester GPA: " << totalGPA / numberOfCourses << endl;
   }
 // ... (rest of the code is the same)
};

int main() {
 int numberOfStudents;
 int tuitionRate;

 cout << "Enter the number of students and tuition rate: ";
 cin >> numberOfStudents >> tuitionRate;
 
 // Open "input.txt" for writing
 ofstream fout;
 fout.open("input.txt");

 // Write the number of students and tuition rate to the file
 fout << numberOfStudents << " " << tuitionRate << endl;

 // Write the student and course data to the file
 fout << "Lisa Miller 890238 Y 4" << endl;
 fout << "Mathematics MTH345 4 A" << endl;
 fout << "Physics PHY357 3 B" << endl;
 fout << "ComputerSci CSC478 3 B" << endl;
 fout << "History HIS356 3 A" << endl;

 // Close the file
 fout.close();

 // Open "input.txt" for reading
 ifstream fin("input.txt");

 int studentID;
 cout << "Enter the student ID: ";
 cin >> studentID;

 for (int i = 0; i < numberOfStudents; i++) {
     string name;
     int id;
     bool isTuitionPaid;
     int numberOfCourses;
     fin >> name >> id >> isTuitionPaid >> numberOfCourses;

     if (id != studentID) {
         cout << "Not registered" << endl;
         continue;
     }

     if (!isTuitionPaid) {
         cout << "The grades for " << name << " have been held for nonpayment of the tuition." << endl;
         cout << "Billing amount: " << numberOfCourses * tuitionRate << endl;
         break;
     }

     Student student(name, id, isTuitionPaid, numberOfCourses);
     student.getData(fin);
     student.displayData();
     break;
 }

 // Close the file
 fin.close();

 return 0;
}