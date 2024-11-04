#include <iostream>
#include <string>
using namespace std;

class Transaction {
private:
    string type;
    double amount;
    static int transactionCount;  // Static variable to track the total number of transactions

public:
    // Constructor increments transaction count on every new transaction
    Transaction(string t = "", double a = 0.0) : type(t), amount(a) {
        transactionCount++;
    }

    // Destructor decrements count when a transaction is deleted
    ~Transaction() {
        transactionCount--;
    }

    // Function to display transaction details
    void displayTransaction() {
        cout << "Transaction Type: " << type << ", Amount: $" << amount << endl;
    }

    double getAmount() {
        return amount;
    }

    // Static function to get the total transaction count
    static int getTransactionCount() {
        return transactionCount;
    }
};

// Initialize static variable
int Transaction::transactionCount = 0;

class Account {
private:
    string accountName;
    double balance;
    Transaction** transactions;
    int transactionCount;
    int maxTransactions;
    static int accountCount;  // Static variable to track the number of accounts

public:
    // Constructor initializes account and increments account count
    Account(string name, double bal, int maxTrans = 10) 
        : accountName(name), balance(bal), transactionCount(0), maxTransactions(maxTrans) {
        transactions = new Transaction*[maxTransactions];
        accountCount++;
    }

    // Destructor frees memory and decrements account count
    ~Account() {
        for (int i = 0; i < transactionCount; i++) {
            delete transactions[i];
        }
        delete[] transactions;
        accountCount--;
    }

    // Adds a transaction to the account
    void addTransaction(string type, double amount) {
        if (transactionCount < maxTransactions) {
            transactions[transactionCount] = new Transaction(type, amount);
            transactionCount++;

            if (amount > 0) {
                balance += amount;
                cout << "Added income of $" << amount << " to " << accountName << endl;
            } else {
                balance += amount;
                cout << "Added expense of $" << -amount << " to " << accountName << endl;
            }
        } else {
            cout << "Transaction limit reached! Cannot add more transactions." << endl;
        }
    }

    void displayBalance() {
        cout << "Current Balance in " << accountName << ": $" << balance << endl;
    }

    void displayAllTransactions() {
        cout << "Transactions for " << accountName << ":" << endl;
        for (int i = 0; i < transactionCount; i++) {
            transactions[i]->displayTransaction();
        }
    }

    // Static function to get the total account count
    static int getAccountCount() {
        return accountCount;
    }
};

// Initialize static variable
int Account::accountCount = 0;

int main() {
    // Creating instances of Account
    Account myAccount("Savings Account", 1000.0);
    Account anotherAccount("Checking Account", 500.0);

    // Adding transactions to accounts
    myAccount.addTransaction("Income", 500.0);
    myAccount.addTransaction("Expense", -200.0);
    anotherAccount.addTransaction("Income", 300.0);

    // Display balance and transactions for each account
    myAccount.displayBalance();
    myAccount.displayAllTransactions();

    anotherAccount.displayBalance();
    anotherAccount.displayAllTransactions();

    // Using static member functions to display total counts
    cout << "Total Accounts Created: " << Account::getAccountCount() << endl;
    cout << "Total Transactions Created: " << Transaction::getTransactionCount() << endl;

    return 0;
}
