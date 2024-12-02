#include <iostream>
#include <string>
using namespace std;

// Abstract base class for Transactions
class TransactionBase {
public:
    virtual void displayTransaction() = 0; // Pure virtual function for displaying transaction
    virtual ~TransactionBase() = default; // Virtual destructor for proper cleanup
};

// Derived class for Transaction
class Transaction : public TransactionBase {
private:
    string type;
    double amount;
    static int transactionCount; // Static variable to track the total number of transactions

public:
    // Constructor increments transaction count on every new transaction
    Transaction(string t = "", double a = 0.0) : type(t), amount(a) {
        transactionCount++;
    }

    // Destructor decrements count when a transaction is deleted
    ~Transaction() override {
        transactionCount--;
    }

    // Implementation of pure virtual function from base class
    void displayTransaction() override {
        cout << "Transaction Type: " << type << ", Amount: $" << amount << endl;
    }

    // Static function to get the total transaction count
    static int getTransactionCount() {
        return transactionCount;
    }
};

// Initialize static variable
int Transaction::transactionCount = 0;

// Abstract base class for Accounts
class AccountBase {
public:
    virtual void displayBalance() const = 0;  // Pure virtual function for displaying balance
    virtual void displayAllTransactions() const = 0; // Pure virtual function for displaying transactions
    virtual ~AccountBase() = default; // Virtual destructor for proper cleanup
};

// Derived class for Account
// **Single Inheritance**: Account inherits from AccountBase
class Account : public AccountBase {
protected:
    string accountName;
    double balance;
    TransactionBase** transactions;
    int transactionCount;
    int maxTransactions;

public:
    // Constructor initializes account and allocates memory for transactions
    Account(string name, double bal, int maxTrans = 10)
        : accountName(name), balance(bal), transactionCount(0), maxTransactions(maxTrans) {
        transactions = new TransactionBase*[maxTransactions];
        // Constructor: Allocates memory for transactions array
    }

    // Destructor frees memory for transactions
    ~Account() override {
        for (int i = 0; i < transactionCount; i++) {
            delete transactions[i];
        }
        delete[] transactions;
        // Destructor: Frees memory for transactions array
    }

    // Adds a transaction to the account
    void addTransaction(const string& type, double amount) {
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

    // Implementation of pure virtual functions from base class
    void displayBalance() const override {
        cout << "Current Balance in " << accountName << ": $" << balance << endl;
    }

    void displayAllTransactions() const override {
        cout << "Transactions for " << accountName << ":" << endl;
        for (int i = 0; i < transactionCount; i++) {
            transactions[i]->displayTransaction();
        }
    }
};

// Derived class for SavingsAccount
// **Multilevel Inheritance**: SavingsAccount inherits from Account, which inherits from AccountBase
class SavingsAccount : public Account {
private:
    double interestRate; // Additional attribute for interest rate

public:
    // Constructor initializes savings account with interest rate
    SavingsAccount(string name, double bal, double rate, int maxTrans = 10)
        : Account(name, bal, maxTrans), interestRate(rate) {}

    // Method to apply interest to the balance
    void applyInterest() {
        balance += (balance * interestRate / 100);
        cout << "Interest applied! New balance: $" << balance << endl;
    }
};

// Menu Display Function
void displayMenu() {
    cout << "\n*** Expense Tracker Menu ***\n";
    cout << "1. Add Transaction\n";
    cout << "2. Display Balance\n";
    cout << "3. Display All Transactions\n";
    cout << "4. Apply Interest (Savings Account Only)\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    string accountName;
    double initialBalance, interestRate;

    cout << "Welcome to the Expense Tracker!" << endl;
    cout << "Enter the account name: ";
    getline(cin, accountName);
    cout << "Enter the initial balance: ";
    cin >> initialBalance;
    cout << "Enter the interest rate (for savings account): ";
    cin >> interestRate;

    // Create a SavingsAccount object
    SavingsAccount myAccount(accountName, initialBalance, interestRate);

    int choice = 0;

    while (choice != 5) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string type;
                double amount;
                cout << "Enter transaction type (Income/Expense): ";
                cin.ignore(); // Clear input buffer
                getline(cin, type);
                cout << "Enter transaction amount (positive for income, negative for expense): ";
                cin >> amount;
                myAccount.addTransaction(type, amount);
                break;
            }
            case 2:
                myAccount.displayBalance();
                break;
            case 3:
                myAccount.displayAllTransactions();
                break;
            case 4:
                myAccount.applyInterest(); // Apply interest for savings account
                break;
            case 5:
                cout << "Exiting the Expense Tracker. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
