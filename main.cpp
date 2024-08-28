#include <iostream>
#include <string>
using namespace std;

// Class for managing individual transactions
class Transaction {
private:
    string type;    // "Income" or "Expense"
    double amount;

public:
    // Constructor using the `this` pointer
    Transaction(string t = "", double a = 0.0) {
        this->type = t;  // `this->type` refers to the current object's type
        this->amount = a; // `this->amount` refers to the current object's amount
    }

    // Member function to display the transaction details
    void displayTransaction() {
        cout << "Transaction Type: " << type << ", Amount: $" << amount << endl;
    }

    // Member function to get the transaction amount
    double getAmount() {
        return amount;
    }
};

// Class for managing a financial account
class Account {
private:
    string accountName;
    double balance;
    Transaction transactions[10];  // Array of Transaction objects
    int transactionCount;          // Number of transactions

public:
    // Constructor using the `this` pointer
    Account(string name, double bal) {
        this->accountName = name;  // `this->accountName` refers to the current object's accountName
        this->balance = bal;       // `this->balance` refers to the current object's balance
        this->transactionCount = 0;  // Initialize transaction count to 0
    }

    // Member function to add a transaction (either income or expense)
    void addTransaction(Transaction t) {
        if (transactionCount < 10) {  // Ensure we don't exceed array bounds
            this->transactions[transactionCount] = t;
            transactionCount++;

            if (t.getAmount() > 0) {
                this->balance += t.getAmount();
                cout << "Added income of $" << t.getAmount() << " to " << this->accountName << endl;
            } else {
                this->balance += t.getAmount();  // Deduct if expense
                cout << "Added expense of $" << -t.getAmount() << " to " << this->accountName << endl;
            }
        } else {
            cout << "Transaction limit reached! Cannot add more transactions." << endl;
        }
    }

    // Member function to display the account balance
    void displayBalance() {
        cout << "Current Balance in " << this->accountName << ": $" << this->balance << endl;
    }

    // Member function to display all transactions
    void displayAllTransactions() {
        cout << "Transactions for " << this->accountName << ":" << endl;
        for (int i = 0; i < transactionCount; i++) {
            transactions[i].displayTransaction();
        }
    }
};

int main() {
    // Creating objects for classes
    Account myAccount("Savings Account", 1000.0);
    Transaction income("Income", 500.0);
    Transaction expense("Expense", -200.0);

    // Using member functions
    myAccount.addTransaction(income);
    myAccount.addTransaction(expense);

    myAccount.displayBalance();
    myAccount.displayAllTransactions();

    return 0;
}
