#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    static int nextAccNumber;
    int accNum;
    string accHolder;
    double balance;

public:
    BankAccount() {
        accNum = ++nextAccNumber;
        accHolder = "N/A";
        balance = 0.0;
    }

    BankAccount(string holder) {
        accNum = ++nextAccNumber;
        accHolder = holder;
        balance = 0.0;
    }

    int getAccNum() const {
        return accNum;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited " << amount << " into account " << accNum << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Withdrawn " << amount << " from account " << accNum << endl;
            return true;
        }
        cout << "Insufficient funds in account " << accNum << endl;
        return false;
    }

    static int getTotalAccounts() {
        return nextAccNumber;
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accNum << endl;
        cout << "Account Holder: " << accHolder << endl;
        cout << "Balance: " << balance << endl;
    }
};

int BankAccount::nextAccNumber = 0;

class BankManager {
private:
    static const int maxAccounts = 100;
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

    void deleteAccount(int accNum) {
        for (int i = 0; i < numAccounts; i++) {
            if (accounts[i].getAccNum() == accNum) {
                for (int j = i; j < numAccounts - 1; j++) {
                    accounts[j] = accounts[j + 1];
                }
                numAccounts--;
                cout << "Account " << accNum << " has been deleted." << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    BankAccount* findAccount(int accNum) {
        for (int i = 0; i < numAccounts; i++) {
            if (accounts[i].getAccNum() == accNum) {
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

    while (1) {
        cout << "Bank Management System Menu:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Delete Account" << endl;
        cout << "3. Find Account" << endl;
        cout << "4. Display All Accounts" << endl;
        cout << "5. Deposit" << endl;
        cout << "6. Withdraw" << endl;
        cout << "7. Exit" << endl;
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
                int accNum;
                cout << "Enter the account number to delete: ";
                cin >> accNum;
                bankManager.deleteAccount(accNum);
                break;
            }
            case 3: {
                int accNum;
                cout << "Enter the account number to find: ";
                cin >> accNum;
                BankAccount* account = bankManager.findAccount(accNum);
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
            case 5: {
                int accNum;
                cout << "Enter the account number to deposit into: ";
                cin >> accNum;
                BankAccount* account = bankManager.findAccount(accNum);
                if (account) {
                    double amount;
                    cout << "Enter the amount to deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
       case 6: {
    int accNum;
    cout << "Enter the account number to withdraw from: ";
    cin >> accNum;
    BankAccount* account = bankManager.findAccount(accNum);
    if (account) {
        double amount;
        cout << "Enter the amount to withdraw: ";
        cin >> amount;
        
        if ((*account).withdraw(amount)) {
            cout << "Withdrawal successful." << endl;
        } else {
            cout << "Withdrawal failed due to insufficient funds." << endl;
        }
    } else {
        cout << "Account not found." << endl;
    }
    break;
}

            case 7:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
