#include <iostream>
#include <string>
using namespace std;
class Student {
private:
    struct StudentRecord {
        string name;
        int age;
    };

    StudentRecord* studentArray;
    int size;
    int capacity;

public:
    Student(int initialCapacity) {
        capacity = initialCapacity;
        size = 0;
        studentArray = new StudentRecord[capacity];
    }

    Student(const Student& other) {
        capacity = other.capacity;
        size = other.size;
        studentArray = new StudentRecord[capacity];
        for (int i = 0; i < size; i++) {
            studentArray[i].name = other.studentArray[i].name;
            studentArray[i].age = other.studentArray[i].age;
        }
    }

    ~Student() {
        delete[] studentArray;
    }

    void addStudent(const string& name, int age) {
        if (size == capacity) {
            capacity *= 2;
            StudentRecord* newStudentArray = new StudentRecord[capacity];
            for (int i = 0; i < size; i++) {
                newStudentArray[i] = studentArray[i];
            }
            delete[] studentArray;
            studentArray = newStudentArray;
        }

        studentArray[size].name = name;
        studentArray[size].age = age;
        size++;
    }

    void displayStudents() {
        for (int i = 0; i < size; i++) {
            cout << "Name: " << studentArray[i].name << ", Age: " << studentArray[i].age << endl;
        }
    }
};

int main() {
    Student studentList(3);

    studentList.addStudent("Mashaal", 20);
    studentList.addStudent("ishtiaq", 22);
    studentList.addStudent("xyz", 21);

    cout << "Original Student List:" << endl;
    studentList.displayStudents();

    Student copiedStudentList = studentList;

    studentList.addStudent("abc", 23);

    cout << "Modified Original Student List:" << endl;
    studentList.displayStudents();
    cout << "Copied Student List (Unchanged):" << endl;
    copiedStudentList.displayStudents();

    return 0;
}
