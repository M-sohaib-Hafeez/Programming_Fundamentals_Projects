
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct BankAccount {
    string accNum;
    string name;
    double balance;
};

void saveAccounts(BankAccount accounts[], int count) {
    ofstream file("accounts.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        file << accounts[i].accNum << endl;
        file << accounts[i].name << endl;
        file << accounts[i].balance << endl;
    }

    file.close();
    cout << "Accounts saved successfully to accounts.txt!\n";
}

void loadAccounts(BankAccount accounts[], int &count) {
    ifstream file("accounts.txt");
    if (!file) {
        cout << "No existing data found. Starting fresh.\n";
        return;
    }

    count = 0;
    while (getline(file, accounts[count].accNum)) {
        getline(file, accounts[count].name);
        file >> accounts[count].balance;
        file.ignore();  // Ignore leftover newline after reading balance
        count++;
    }

    file.close();
    cout << "Accounts loaded successfully from accounts.txt!\n";
}

void createAccount(BankAccount accounts[], int &count) {
    BankAccount newAccount;
    cout << "Enter account number: ";
    cin >> newAccount.accNum;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newAccount.name);
    cout << "Enter initial deposit: ";
    cin >> newAccount.balance;

    accounts[count] = newAccount;
    count++;

    saveAccounts(accounts, count);
    cout << "Account created successfully!\n";
}

void depositMoney(BankAccount accounts[], int count) {
    string accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accNum == accNum) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            accounts[i].balance += amount;
            saveAccounts(accounts, count);
            cout << "Deposited successfully. New balance: $" << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account not found!\n";
}

void checkBalance(BankAccount accounts[], int count) {
    string accNum;
    cout << "Enter account number: ";
    cin >> accNum;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accNum == accNum) {
            cout << "Account Number: " << accounts[i].accNum << endl;
            cout << "Name: " << accounts[i].name << endl;
            cout << "Current Balance: $" << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account not found!\n";
}

int main() {
    BankAccount accounts[10];
    int count = 0;

    loadAccounts(accounts, count);

    int choice;
    do {
        cout << "\nBanking System Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Check Balance\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            createAccount(accounts, count);
        } else if (choice == 2) {
            depositMoney(accounts, count);
        } else if (choice == 3) {
            checkBalance(accounts, count);
        } else if (choice == 4) {
            cout << "Exiting the system. Goodbye! :)\n";
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
