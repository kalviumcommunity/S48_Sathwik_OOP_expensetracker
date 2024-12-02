#include <iostream>
#include <string>
using namespace std;

// Abstract base class for Transactions
class TransactionBase {
public:
    virtual void displayTransaction() = 0; // Pure virtual function for displaying transaction (Abstract Class)
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
    void displayTransaction() override { // Virtual Function Implementation
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
    virtual void displayBalance() const = 0;  // Pure virtual function for displaying balance (Abstract Class)
    virtual void displayAllTransactions() const = 0; // Pure virtual function for displaying transactions
    virtual ~AccountBase() = default; // Virtual destructor for proper cleanup
};

// Derived class for Account
class Account : public AccountBase {
protected:
    string accountName;
    double balance;
    TransactionBase** transactions; // Array of pointers to TransactionBase (polymorphism usage)
    int transactionCount;
    int maxTransactions;

public:
    // Constructor initializes account and allocates memory for transactions
    Account(string name, double bal, int maxTrans = 10)
        : accountName(name), balance(bal), transactionCount(0), maxTransactions(maxTrans) {
        transactions = new TransactionBase*[maxTransactions];
    }

    // Destructor frees memory for transactions
    ~Account() override {
        for (int i = 0; i < transactionCount; i++) {
            delete transactions[i];
        }
        delete[] transactions;
    }

    // Adds a transaction to the account
    void addTransaction(const string& type, double amount) {
        if (transactionCount < maxTransactions) {
            transactions[transactionCount] = new Transaction(type, amount); // Storing derived class in base class pointer
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
            transactions[i]->displayTransaction(); // Polymorphic call to displayTransaction
        }
    }
};

// Derived class for SavingsAccount
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

// **SOLID Principle 3 (Liskov Substitution Principle)** 
// Adding new derived class for RecurringTransaction ensures it behaves like Transaction 
// without breaking the existing code functionality.
class RecurringTransaction : public Transaction {
private:
    int recurrenceCount; // Number of recurrences

public:
    RecurringTransaction(string t, double a, int count)
        : Transaction(t, a), recurrenceCount(count) {}

    // Override displayTransaction to include recurrence details
    void displayTransaction() override {
        Transaction::displayTransaction();
        cout << "Recurring for " << recurrenceCount << " times." << endl;
    }
};

// **SOLID Principle 1 (Single Responsibility Principle)**
class MenuHandler {
public:
    static void displayMenu() {
        cout << "\n*** Expense Tracker Menu ***\n";
        cout << "1. Add Single Transaction\n";
        cout << "2. Display Balance\n";
        cout << "3. Display All Transactions\n";
        cout << "4. Add Recurring Transaction\n"; // New menu option for recurring transactions
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
    }

    static void handleInput(SavingsAccount& account) {
        int choice = 0;
        while (choice != 5) {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    string type;
                    double amount;
                    cout << "Enter transaction type (Income/Expense): ";
                    cin.ignore();
                    getline(cin, type);
                    cout << "Enter transaction amount (positive for income, negative for expense): ";
                    cin >> amount;
                    account.addTransaction(type, amount);
                    break;
                }
                case 2:
                    account.displayBalance();
                    break;
                case 3:
                    account.displayAllTransactions();
                    break;
                case 4: {
                    string type;
                    double amount;
                    int recurrence;
                    cout << "Enter recurring transaction type: ";
                    cin.ignore();
                    getline(cin, type);
                    cout << "Enter transaction amount: ";
                    cin >> amount;
                    cout << "Enter recurrence count: ";
                    cin >> recurrence;

                    // Liskov Substitution Principle applied here:
                    // RecurringTransaction used where TransactionBase is expected
                    RecurringTransaction rt(type, amount, recurrence);
                    rt.displayTransaction();
                    break;
                }
                case 5:
                    cout << "Exiting. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        }
    }
};

int main() {
    string accountName;
    double initialBalance, interestRate;

    cout << "Welcome to the Expense Tracker!" << endl;
    cout << "Enter the account name: ";
    getline(cin, accountName);
    cout << "Enter the initial balance: ";
    cin >> initialBalance;
    cout << "Enter the interest rate (Savings Account): ";
    cin >> interestRate;

    // Create SavingsAccount
    SavingsAccount myAccount(accountName, initialBalance, interestRate);

    // Delegate menu handling to MenuHandler
    MenuHandler::handleInput(myAccount);

    return 0;
}
