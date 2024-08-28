#include <iostream>
#include <string>
using namespace std;

// Class for managing individual transactions
class Transaction {
private:
    string type;    // "Income" or "Expense"
    double amount;

public:
    // Constructor
    Transaction(string t, double a) : type(t), amount(a) {}

    // Member function to display the transaction details
    void displayTransaction() {
        cout << "Transaction Type: " << type << ", Amount: " << amount << endl;
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

public:
    // Constructor
    Account(string name, double bal) : accountName(name), balance(bal) {}

    // Member function to add a transaction (either income or expense)
    void addTransaction(Transaction t) {
        if (t.getAmount() > 0) {
            balance += t.getAmount();
            cout << "Added income of " << t.getAmount() << " to " << accountName << endl;
        } else {
            balance += t.getAmount();  // Deduct if expense
            cout << "Added expense of " << -t.getAmount() << " to " << accountName << endl;
        }
    }

    // Member function to display the account balance
    void displayBalance() {
        cout << "Current Balance in " << accountName << ": " << balance << endl;
    }
};

int main() {
    // Creating objects for classes
    Account myAccount("Savings Account", 1000.0);
    Transaction income("Income", 500.0);
    Transaction expense("Expense", -200.0);

    // Using member functions
    myAccount.addTransaction(income);
    myAccount.displayBalance();

    myAccount.addTransaction(expense);
    myAccount.displayBalance();

    return 0;
}
