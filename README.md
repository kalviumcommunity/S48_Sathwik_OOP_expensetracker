# S48_Sathwik_OOP_expensetracker
Expense Tracker Simulation
Project Overview
The Expense Tracker Simulation is a console-based application developed in C++ that simulates real-world personal finance management. The project allows users to create virtual accounts, record transactions, categorize expenses, and monitor their spending habits. It demonstrates core Object-Oriented Programming (OOP) principles such as encapsulation, inheritance, and polymorphism.

Features
Account Management:
Create multiple virtual accounts with the ability to set an initial balance.

Expense and Income Tracking:
Record income and expenses, categorize them, and update account balances.

Budgeting:
Set and monitor monthly budgets for different expense categories (feature planned).

Reporting:
Generate and display reports on spending trends over time (feature planned).

Classes
1. Transaction
Attributes:
type (string): The type of transaction ("Income" or "Expense").
amount (double): The transaction amount.
Member Functions:
displayTransaction(): Displays the transaction details.
getAmount(): Returns the transaction amount.


2. Account
Attributes:
accountName (string): The name of the account.
balance (double): The current balance of the account.
Member Functions:
addTransaction(Transaction t): Adds a transaction and updates the account balance.
displayBalance(): Displays the current balance of the account.
