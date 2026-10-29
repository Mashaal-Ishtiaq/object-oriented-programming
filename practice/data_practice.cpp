
#include <iostream>
using namespace std;
int main() {
    int* numbers = 0; 
    int size = 0; 
    int capacity = 1;

    numbers = new int[capacity];

    cout << "Enter numbers (enter -1 to exit):" << endl;

    int num;
    while (1) {
        cin >> num;

        if (num == -1) {
            break;
        }

        if (size == capacity) {
            capacity *= 2; 
            int* newNumbers = new int[capacity];
            for (int i = 0; i < size; ++i) {
                newNumbers[i] = numbers[i];
            }
            delete[] numbers;
            numbers = newNumbers;
        }

        numbers[size] = num;
        size++;
    }

    cout << "Entered numbers: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    delete[] numbers;

    return 0;
}
