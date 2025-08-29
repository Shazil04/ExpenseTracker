#include <iostream>
#include <vector>
using namespace std;
class Expense {
    private:int ID ;
    private:string date;
    private:string category;
    private:double amount;
    private:string note;

public:
    Expense(int ID , const string& date , const string &category , double amount , const string & note){
        this->ID = ID;
        this->date = date;
        this->category = category;
        this->amount = amount;
        this->note = note;
    }
public:
    void setDate(const string &newDate) {
        this->date = newDate;
    }
public:
    void setCategory(const string &newCategory) {
        this->category = newCategory;
    }
public:
    void setNote(const string &newNote) {
        this->note = newNote;
    }

public:
    void setAmount(double myAmount) {
        if (myAmount < 0) {
            cout << "Invalid Amount " << myAmount << endl;
        }
        else {
            amount = myAmount;
        }
    }
public:
    int getID()const  {
        return ID;
    }
public:
    string getCategory() const{
        return category;
    }
public:
    double getAmount() const {
        return amount;
    }
public:
    string getDate()const {
        return date;
    }
public:
    void display() const{
        cout << "ID: " << ID << "  ";
        cout << "date: " << date << "  ";
        cout << "category: " << category << "  ";
        cout << "amount: " << amount << "  ";
        cout << "note: " << note << "  " ;
    }
};

class ExpensesTracker {
    vector<Expense> expenses;
    int nxtID = 0;

public:
    void addExpense() {
        int newID = ++nxtID;
        cout << "Adding Expense " << endl;
        cout << "Enter Date (DD/MM/YYYY): ";
        string newDate;
        getline(cin , newDate);

        cout << "Category: ";
        string newCategory;
        getline(cin , newCategory);

        cout << "Amount: ";
        double newAmount;
        cin >> newAmount;

        cin.ignore();

        cout << "Note: ";
        string newNote;
        getline(cin , newNote);
        Expense e1(newID, newDate, newCategory, newAmount, newNote);
        expenses.push_back(e1);
}
public:
    void viewExpenses() const {
        for (const Expense &e : expenses) {
            e.display();
        }
    }
public:
    void searchByDate(const string &userDate)const{
        bool found = false;
        for (const Expense &e : expenses){
            if (e.getDate() == userDate) {
                e.display();
                found = true;
            }
        }
        if (!found) {
            cout << "Not found: Expense not found" << endl;
        }
    }
public:
    void searchByCategory(const string &userCategory)const{
        bool found = false;
        for (const Expense &e : expenses){
            if (e.getCategory() == userCategory) {
                e.display();
                found = true;
            }
        }
        if (!found) {
            cout << "Not found: Expense not found" << endl;
        }
    }
public:
    void deleteExpense(const int ID){
        for (auto it = expenses.begin(); it != expenses.end(); ++it) {
            if (it->getID() == ID) {
                expenses.erase(it);
                cout << "Expense with ID " << ID << " deleted." << endl;
                return;

            }
        }
        cout << "Expense with ID " << ID << " not found." << endl;
    }
public:
    void editExpense(const int ID) {
        for (Expense &e : expenses) {
            if (e.getID()== ID) {
                e.display();
                while (true) {
                    cout << "What do you want to edit: " << endl;
                    cout << "1. Date " << endl;
                    cout << "2. Category " << endl;
                    cout << "3. Amount" << endl;
                    cout << "4. Note" << endl;
                    cout << "5. exit" << endl;
                    int choice;
                    cin >> choice;
                    cin.ignore();
                    if (choice == 1) {
                        cout << "Enter Date (DD/MM/YYYY): ";
                        string newDate;
                        getline(cin , newDate);
                        e.setDate(newDate);
                        cout << "Expense with ID " << ID << " edited." << endl;

                    }
                    else if (choice == 2) {
                        cout << "Enter Category " << endl;
                        string newCategory;
                        getline(cin , newCategory);
                        e.setCategory(newCategory);
                        cout << "Expense with ID " << ID << " edited." << endl;

                    }
                    else if (choice == 3) {
                        cout << "Enter Amount " << endl;
                        double newAmount;
                        cin >> newAmount;
                        e.setAmount(newAmount);
                        cout << "Expense with ID " << ID << " edited." << endl;
                    }
                    else if (choice == 4) {
                        cout << "Enter Note " << endl;
                        string newNote;
                        getline(cin , newNote);
                        e.setNote(newNote);
                        cout << "Expense with ID " << ID << " edited." << endl;

                    }
                    else if (choice == 5) {
                        break;

                    }
                    else {
                        cout << "Invalid choice." << endl;
                    }


                }
            }
            }

    }


};

int main() {

    cout << "Expense Tracker Project Initialized!" << endl;
    return 0;
}
