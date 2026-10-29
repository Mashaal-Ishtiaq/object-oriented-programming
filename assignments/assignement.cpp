#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    static int nextAccountNumber;
    int accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount() {
        accountNumber = ++nextAccountNumber;
        accountHolder = "N/A";
        balance = 0.0;
    }

    BankAccount(string holder) {
        accountNumber = ++nextAccountNumber;
        accountHolder = holder;
        balance = 0.0;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " into account " << accountNumber << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Withdrawn $" << amount << " from account " << accountNumber << endl;
            return true;
        }
        cout << "Insufficient funds in account " << accountNumber << endl;
        return false;
    }

    static int getTotalAccounts() {
        return nextAccountNumber;
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }
};

int BankAccount::nextAccountNumber = 0; 

class BankManager {
private:
    static const int maxAccounts = 100; // Maximum number of accounts
    BankAccount accounts[maxAccounts];
    int numAccounts = 0;

public:
    BankAccount* createAccount(const string& holder) {
        if (numAccounts < maxAccounts) {
            BankAccount newAccount(holder);
            accounts[numAccounts] = newAccount;
            numAccounts++;
            return &accounts[numAccounts - 1];
        } else {
            cout << "Maximum number of accounts reached." << endl;
            return nullptr;
        }
    }

    void deleteAccount(int accountNumber) {
        for (int i = 0; i < numAccounts; i++) {
            if (accounts[i].getAccountNumber() == accountNumber) {
                for (int j = i; j < numAccounts - 1; j++) {
                    accounts[j] = accounts[j + 1];
                }
                numAccounts--;
                cout << "Account " << accountNumber << " has been deleted." << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    BankAccount* findAccount(int accountNumber) {
        for (int i = 0; i < numAccounts; i++) {
            if (accounts[i].getAccountNumber() == accountNumber) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    void displayAllAccounts() {
        cout << "All Accounts: " << endl;
        for (int i = 0; i < numAccounts; i++) {
            accounts[i].displayAccountInfo();
            cout << endl;
        }
    }
};

int main() {
    BankManager bankManager;

    while (true) {
        cout << "Bank Management System Menu:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Delete Account" << endl;
        cout << "3. Find Account" << endl;
        cout << "4. Display All Accounts" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string holderName;
                cout << "Enter the account holder's name: ";
                cin >> holderName;
                bankManager.createAccount(holderName);
                break;
            }
            case 2: {
                int accountNumber;
                cout << "Enter the account number to delete: ";
                cin >> accountNumber;
                bankManager.deleteAccount(accountNumber);
                break;
            }
            case 3: {
                int accountNumber;
                cout << "Enter the account number to find: ";
                cin >> accountNumber;
                BankAccount* account = bankManager.findAccount(accountNumber);
                if (account) {
                    account->displayAccountInfo();
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 4:
                bankManager.displayAllAccounts();
                break;
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
