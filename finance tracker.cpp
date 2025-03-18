#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // For generating OTP
#include <ctime>    // For OTP randomness

using namespace std;

class FinanceTracker {
private:
    struct Transaction {
        string description;
        double amount;
        string type; // "Income" or "Expense"
    };

    struct Investment {
        string name;
        double value;
    };

    vector<Transaction> transactions;
    vector<Investment> investments;
    double budget;

public:
    FinanceTracker(double initBudget) : budget(initBudget) {}

    void trackTransaction(const string& description, double amount, const string& type) {
        transactions.push_back({description, amount, type});
        cout << "Transaction added: " << description << " | " << type << " | " << amount << endl;
    }

    void showTransactions() {
        cout << "\n---- Transaction History ----" << endl;
        for (auto& t : transactions) {
            cout << t.description << " | " << t.type << " | " << t.amount << endl;
        }
    }

    void setBudget(double newBudget) {
        budget = newBudget;
        cout << "Budget set to: " << budget << endl;
    }

    void showBudgetStatus() {
        double totalExpenses = 0, totalIncome = 0;
        for (auto& t : transactions) {
            if (t.type == "Expense") totalExpenses += t.amount;
            else if (t.type == "Income") totalIncome += t.amount;
        }
        cout << "Total Income: " << totalIncome << endl;
        cout << "Total Expenses: " << totalExpenses << endl;
        cout << "Remaining Budget: " << budget - totalExpenses << endl;
    }

    void addInvestment(const string& name, double value) {
        investments.push_back({name, value});
        cout << "Investment added: " << name << " | " << value << endl;
    }

    void showInvestments() {
        cout << "\n---- Investments ----" << endl;
        for (auto& inv : investments) {
            cout << inv.name << " | " << inv.value << endl;
        }
    }

    void showDashboard() {
        cout << "\n=========== Dashboard ===========\n";
        showBudgetStatus();
        cout << "\nTransaction Count: " << transactions.size();
        cout << "\nInvestment Count: " << investments.size();
        cout << "\n=================================\n";
    }
};

class User {
private:
    string username = "Ubaidullah";
    string password = "ubaid1613";

public:
    bool authenticate(const string& enteredUsername, const string& enteredPassword) {
        return enteredUsername == username && enteredPassword == password;
    }

    bool verifyOTP() {
        srand(time(0));
        int otp = rand() % 9000 + 1000;
        cout << "Your OTP is: " << otp << endl;

        int enteredOTP;
        cout << "Enter the OTP: ";
        cin >> enteredOTP;

        return enteredOTP == otp;
    }
};

int main() {
    string enteredUsername, enteredPassword;

    User user;
    cout << "Please enter your username to login: ";
    cin >> enteredUsername;
    cout << "Please enter your password to login: ";
    cin >> enteredPassword;

    if (!user.authenticate(enteredUsername, enteredPassword)) {
        cout << "Invalid username or password!" << endl;
        return 0;
    }

    cout << "Verifying 2FA...\n";
    if (!user.verifyOTP()) {
        cout << "Invalid OTP! Access Denied.\n";
        return 0;
    }

    cout << "Login successful!" << endl;
    FinanceTracker tracker(1000.0);

    int choice;
    do {
        cout << "\n1. Track Transaction\n2. Show Transactions\n3. Set Budget\n4. Show Budget Status\n5. Add Investment\n6. Show Investments\n7. View Dashboard\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string description, type;
                double amount;
                cout << "Enter transaction description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter type (Income/Expense): ";
                cin >> type;
                tracker.trackTransaction(description, amount, type);
                break;
            }
            case 2:
                tracker.showTransactions();
                break;
            case 3: {
                double newBudget;
                cout << "Enter new budget amount: ";
                cin >> newBudget;
                tracker.setBudget(newBudget);
                break;
            }
            case 4:
                tracker.showBudgetStatus();
                break;
            case 5: {
                string name;
                double value;
                cout << "Enter investment name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter investment value: ";
                cin >> value;
                tracker.addInvestment(name, value);
                break;
            }
            case 6:
                tracker.showInvestments();
                break;
            case 7:
                tracker.showDashboard();
                break;
            case 8:
                cout << "Exiting system..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}