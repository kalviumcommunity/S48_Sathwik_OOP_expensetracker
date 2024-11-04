#include <iostream>
#include <string>
using namespace std;

class Transaction {
private:
    string type;
    double amount;

public:
    Transaction(string t = "", double a = 0.0) : type(t), amount(a) {}

    void displayTransaction() {
        cout << "Transaction Type: " << type << ", Amount: $" << amount << endl;
    }

    double getAmount() {
        return amount;
    }
};

class Account {
private:
    string accountName;
    double balance;
    Transaction** transactions;  // Pointer to array of Transaction pointers
    int transactionCount;
    int maxTransactions;  // Limit for the number of transactions

public:
    Account(string name, double bal, int maxTrans = 10) : accountName(name), balance(bal), transactionCount(0), maxTransactions(maxTrans) {
        transactions = new Transaction*[maxTransactions];  // Allocate array of pointers
    }

    ~Account() {
        for (int i = 0; i < transactionCount; i++) {
            delete transactions[i];  // Free each Transaction object
        }
        delete[] transactions;  // Free the array of pointers
    }

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
};

int main() {
    Account myAccount("Savings Account", 1000.0);

    myAccount.addTransaction("Income", 500.0);
    myAccount.addTransaction("Expense", -200.0);

    myAccount.displayBalance();
    myAccount.displayAllTransactions();

    return 0;
}
