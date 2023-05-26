#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Define a structure for a bank account
struct Account {
    int account_number;
    string name;
    double balance;
    int id;
    int age;
    string job;
    Account* next;
};

// Function prototypes
/*void checkAge(int age){
    if(age<18)
    {
        cout<<"You have to be older than 18";
    }
    else
    {

    }
}
 */
void addAccount(Account*& head);
void deposit(Account* head, int account_number, double amount);
void withdraw(Account* head, int account_number, double amount);
double checkBalance(Account* head, int account_number);
void searchAccount(Account* head, int account_number);
void writeAccountsToFile(Account* head);
void readAccountsFromFile(Account*& head);

int main() {
    // Initialize the linked list and read accounts from file
    Account* head = nullptr;
    readAccountsFromFile(head);

    int choice;
    do {
        // Display menu
        cout << "Bank System\n";
        cout << "1. Add account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check balance\n";
        cout << "5. Search account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Processuser choice
        switch (choice) {
            case 1: addAccount(head); writeAccountsToFile(head); break;
            case 2: {
                int account_number,age,id;
                double amount;

                int checkAge( age);
                cout << "Enter account number: ";
                cin >> account_number;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                deposit(head, account_number, amount);
                writeAccountsToFile(head);
                break;
            }
            case 3: {
                int account_number;
                double amount;
                cout << "Enter account number: ";
                cin >> account_number;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                withdraw(head, account_number, amount);
                writeAccountsToFile(head);
                break;
            }
            case 4: {
                int account_number;
                cout << "Enter account number: ";
                cin >> account_number;
                double balance = checkBalance(head, account_number);
                if (balance != -1) {
                    cout << "Account balance: " << balance << endl;
                }
                break;
            }
            case 5: {
                int account_number;
                cout << "Enter account number to search: ";
                cin >> account_number;
                searchAccount(head, account_number);
                break;
            }
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice !=6);

    // Free memory used by linked list
    Account* curr = head;
    while (curr != nullptr) {
        Account* temp = curr;
        curr = curr->next;
        delete temp;
    }

    return 0;
}

// Function to add a new account to the linked list
void addAccount(Account*& head) {
    Account* customer = new Account;
    cout << "Enter name: ";
    cin >> customer->name;
    cout<<"Enter ID:  ";
    cin>>customer->id;
    cout<<"Enter Age: ";
    cin>>customer->age;
    if(customer->age<18)
    {
        cout<<"You have to be older than 18 ";
    }
    else {
        cout << "Enter your Job: ";
        cin >> customer->job;
        cout << "Enter initial balance: ";
        cin >> customer->balance;
        cout << "Enter account number: ";
        cin >> customer->account_number;
         }
    customer->next = head;
    head = customer;
}

// Function to deposit money into an account
void deposit(Account* head, int account_number, double amount) {
    Account* curr = head;
    while (curr != nullptr) {
        if (curr->account_number == account_number) {
            curr->balance += amount;
            cout << "Deposit successful. New balance: " << curr->balance << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Account not found.\n";
}

// Function to withdraw money from accounts
void withdraw(Account* head, int account_number, double amount) {
    Account* curr = head;
    while (curr != nullptr) {
        if (curr->account_number == account_number) {
            if (curr->balance >= amount){
                curr->balance -= amount;
                cout << "Withdrawal successful. New balance: " << curr->balance << endl;
            } else {
                cout << "Insufficient balance.\n";
            }
            return;
        }
        curr = curr->next;
    }
    cout << "Account not found.\n";
}

// Function to check the balance of an account
double checkBalance(Account* head, int account_number) {
    Account* curr = head;
    while (curr != nullptr) {
        if (curr->account_number == account_number) {
            return curr->balance;
        }
        curr = curr->next;
    }
    cout << "Account not found.\n";
    return -1;
}

// Function to search for accounts using account number
void searchAccount(Account* head, int account_number) {
    Account* curr = head;
    while (curr != nullptr) {
        if (curr->account_number == account_number) {
            cout << "Account found. Name: " << curr->name << ", Balance: " << curr->balance << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Account not found.\n";
}

// Function to write all accounts to file
void writeAccountsToFile(Account* head) {
    ofstream file("accounts.txt");
    if (file.is_open()) {
        Account* curr = head;
        while (curr != nullptr) {
            file << curr->name << " " <<curr->id<<" "<<curr->age<<" "<<curr->job<<" " << curr->account_number  << " " << curr->balance << endl;
            curr = curr->next;
        }
        file.close();
    } else {
        cout << "Error: could not open file.\n";
    }
}

// Function to read accounts from file and add them to the linked list (display the data)
void readAccountsFromFile(Account*& head) {
    ifstream file("accounts.txt");
    if (file.is_open()) {
        int id;
        int age;
        string job;
        int account_number;
        string name;
        double balance;
        while (file >>  name >>id>>age>>job >>account_number >> balance) {
            Account* temp = new Account;
            temp->name = name;
            temp->id=id;
            temp->age=age;
            temp->job=job;
            temp->account_number = account_number;
            temp->balance = balance;
            temp->next = head;
            head = temp;
        }
        file.close();
    } else {
        cout << "Warning: could not open file. Starting with empty accounts list.\n";
    }
}
