#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;
class Expense {
private:
    int ID ;
    string date;
    string category;
    double amount;
    string note;

public:
    Expense(int ID , const string& date , const string &category , double amount , const string & note){
        this->ID = ID;
        this->date = date;
        this->category = category;
        this->amount = amount;
        this->note = note;
    }
    void setID(const int &newID) {
        this->ID = newID;

    }
    void setDate(const string &newDate) {
        this->date = newDate;
    }

    void setCategory(const string &newCategory) {
        this->category = newCategory;
    }

    void setAmount(double myAmount) {
        if (myAmount < 0) {
            cout << "Invalid Amount " << myAmount << endl;
        }
        else {
            amount = myAmount;
        }
    }
    void setNote(const string &newNote) {
        this->note = newNote;
    }
    int getID()const  {
        return ID;
    }
    string getCategory() const{
        return category;
    }
    double getAmount() const {
        return amount;
    }
    string getDate()const {
        return date;
    }
    string getNote()const {
        return note;
    }
    void display() const {
             cout << left << setw(5) << ID
             << left << setw(10) << date
             << left << setw(15) << category
             << left << setw(15) << amount
             << left << setw(20) << note
             << endl;
    }

};

class ExpensesTracker {
    vector<Expense> expenses;
    int nxtID = 0;

public:
    void addExpense() {
        int newID = ++nxtID;
        cout << "Adding Expense\n";

        string newDate;
        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> newDate;

        string newCategory;
        cout << "Category: ";
        cin >> newCategory;

        double newAmount;
        cout << "Amount: ";
        cin >> newAmount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid amount entered!\n";
            return;
        }

        cin.ignore();

        string newNote;
        cout << "Note: ";
        getline(cin, newNote);

        Expense e1(newID, newDate, newCategory, newAmount, newNote);
        expenses.push_back(e1);
        saveToFile();
    }
    void viewExpenses() const {
        cout << left << setw(5) << "ID"
        << left << setw(10)<< "Date"
        << left << setw(15) << "Category"
        << left << setw(15) << "Amount"
        << left << setw(20) << "Note"
        << endl ;
        for (const Expense &e : expenses){
            e.display();
        }
    }
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
                        getline(cin, newDate);
                        e.setDate(newDate);
                        cout << "Expense with ID " << ID << " edited." << endl;
                    } else if (choice == 2) {
                        cout << "Enter Category " << endl;
                        string newCategory;
                        getline(cin, newCategory);
                        e.setCategory(newCategory);
                        cout << "Expense with ID " << ID << " edited." << endl;
                    } else if (choice == 3) {
                        cout << "Enter Amount " << endl;
                        double newAmount;
                        cin >> newAmount;
                        e.setAmount(newAmount);
                        cout << "Expense with ID " << ID << " edited." << endl;
                    } else if (choice == 4) {
                        cout << "Enter Note " << endl;
                        string newNote;
                        getline(cin, newNote);
                        e.setNote(newNote);
                        cout << "Expense with ID " << ID << " edited." << endl;
                    } else if (choice == 5) {
                        break;
                    } else {
                        cout << "Invalid choice." << endl;
                    }
                }
            }
            }

    }
    void saveToFile() const{
        ofstream write ("Record.txt" , ios::app);
        if (!write.is_open()) {
            cout << "Cannot open file." << endl;
            return;
        }
        for (const Expense &e : expenses) {
            write << e.getID() << ",";
            write << e.getDate() << ",";
            write << e.getCategory() << ",";
            write << e.getAmount() << ",";
            write << e.getNote() << endl;
            cout << "Expense added successfully!\n\n\n";
        }
        write.close();

    }
    void loadFromFile() {
        ifstream read ("Record.txt", ios::in);
        if (!read.is_open()) {
            cout << "Cannot open file." << endl;
            return;

        }
        string line;
        while(getline(read , line)) {
            stringstream ss(line);
            string id , date , category , amount , note;
            getline(ss , id , ',');
            getline(ss , date , ',');
            getline(ss , category , ',');
            getline(ss , amount , ',');
            getline(ss , note);

            int ID = stoi(id);
            double Amount = stod(amount);

            Expense e(ID , date , category , Amount , note);
            expenses.push_back(e);
        }
        read.close();
    }
    void finalReportGenerate() const{
        double totalAmount = 0;
        vector<string> categories = {"food" , " transport" , "entertainment ", "studies ", "debts ", "shopping" , "others"};
        vector<double> categoriesTotal(categories.size(), 0.0);
        for (const Expense &e : expenses) {
            totalAmount += e.getAmount();
            for (int i = 0 ; i < categories.size(); i++) {
                if (categories[i] == e.getCategory()) {
                    categoriesTotal[i] += e.getAmount();
                    break;
                }
            }
        }
        cout << "Total Expenses = " << totalAmount << endl << endl<< endl;
        cout << "/ncategories breakdown:" << endl << "total categories: " << categoriesTotal.size() << endl;
        for (int i = 0; i < categories.size(); i++) {
            cout << categories[i] << ": " << categoriesTotal[i] << endl;
        }
    }
};
class User {
private:
    string username;
    string password;


    // Constructor
public:
    User(const string& u, const string& p) {
        username = u;
        password = p;
    }
    string getUsername() const {
        return username;
    }


    string getPassword() const {
        return password;
    }
    void setUsername(const string& u) {
        username = u;
    }
    void setPassword(const string& p) {
        password = p;

    }

};

class UserManager {
private:
    vector<User> users;

public:
    UserManager() {
        loadFromFile();
    }
    ~UserManager() {
        saveToFile();
    }
    static bool equalIgnoreCase(const string &a , const string &b) {
        if (a.size() != b.size()) {
            return false;
        }
        for (int i = 0; i < a.size(); i++) {
            if (toupper(a[i]) != toupper(b[i])) {
                return false;
            }
        }
        return true;
    }

    static string toFileString(const User &u){
        return u.getUsername() + "," + u.getPassword();
    }

    static User toVectorUser(const string& line) {
        vector<string> parts;
        string token;
        stringstream ss(line);

        while (getline(ss, token, ',')) {
            parts.push_back(token);
        }

        if (parts.size() == 2) {
            return { parts[0], parts[1] };
        }
        throw runtime_error("Invalid format");

    }
    void signUp(){
        cout << "Enter username: ";
        string username;
        getline(cin , username );
        for (const User &myUser : users) {
            if (equalIgnoreCase(myUser.getUsername() , username)) {
                cout << "User already exists." << endl;
                return;
            }
        }
        cout << "Enter password: ";
        string password;
        getline(cin , password);
        cout << "confirm password: ";
        string confirmPassword;
        getline(cin , confirmPassword);
        if (password != confirmPassword) {
            cout << "Password didn't match!" << endl;
            return;
        }
        users.emplace_back(username, password);
        cout << "User created successfully!" << endl;
    }
    void logIn() const{
        while (true) {
            bool confirm = false;
            cout << "Enter username: ";
            string username;
            getline(cin , username );
            cout << "Enter password: ";
            string password;
            getline(cin , password);
            for (const User &myUser : users) {
                if (equalIgnoreCase(myUser.getUsername() , username) && equalIgnoreCase(myUser.getPassword() , password)) {
                    cout << "logged in successfully!" << endl;
                    confirm = true;
                    break;
                }
            }
            if (confirm){
                break;
            }
            cout << "Login failed! Try again.\n";
        }
    }
    void loadFromFile(){
        ifstream read ("userRecord.txt", ios::in);
        if (!read.is_open()) {
            cout << "Cannot open file." << endl;

            return;
        }
        string line;
        while (getline(read, line)) {
            try {
                users.emplace_back(toVectorUser(line));
            } catch (const runtime_error&) {
                cout << "Skipping bad line: " << line << endl;
            }
        }

        read.close();
    }
    void saveToFile() const {
        ofstream write ("userRecord.txt", ios::out);
        if (!write.is_open()) {
            cout << "Cannot open file." << endl;
            return;
        }
        for (const User &myUser : users){
            write << toFileString(myUser) << "\n";

        }
        write.close();
    }
};

class UI {
private:
    ExpensesTracker tracker;
    UserManager users;

public:
    UI(){
        cout << "=============================\n";
        cout << "     EXPENSE TRACKER APP     \n";
        cout << "=============================\n\n";
    }
    ~UI(){
        cout << "Thanks for using expense tracking.\n";
        cout << "============================\n";

    }
    void run() {
        while (true) {
            cout << "choose an option number:" << endl;
            cout << "1. Main Menu \n";
            cout << "2. Register yourself\n";
            cout << "3. Exit\n";
            int choice;
            cin >> choice;
            if (choice == 1) {
                cout << endl << endl;
                while (true) {
                    cout << "Choose an option number:" << endl;
                    cout << "1. Add Expense \n";
                    cout << "2. Remove Expense \n";
                    cout << "3. View All Expenses \n";
                    cout << "4. Search Expense \n";
                    cout << "5. Edit Expense \n";
                    cout << "6. Report of Expenses \n";
                    cout << "7. Exit\n";
                    int option;
                    cin >> option;
                    if (option == 1) {
                        tracker.addExpense();
                    }
                    else if (option == 2) {
                        cout << endl << endl;
                        tracker.viewExpenses();
                        cout << "Enter Expense ID to delete : ";
                        int ID =0 ;
                        do{
                            cin >> ID;
                            if(ID < 0) {
                                cout << "Invalid ID "<< endl << endl;
                            }
                            else{
                                tracker.deleteExpense(ID);
                            }
                        }while(ID > 0);
                    }
                    else if (option == 3) {
                        cout << endl << endl;
                        tracker.viewExpenses();
                    }
                    else if (option == 4) {
                        cout << endl << endl;
                        while (true) {
                            cout << "choose an option number:" << endl;
                            cout << "1. Search by Date\n";
                            cout << "2. Search by category \n";
                            cout << "3. Exit \n";
                            int myOption;
                            cin >> myOption;
                            if (myOption == 1) {
                                cout << "Enter Date to search:" << endl;
                                string date;
                                getline(cin , date);
                                tracker.searchByDate(date);
                            }
                            else if (myOption == 2) {
                                cout << "Enter Category to search:" << endl;
                                cout << endl << endl;
                                string category;
                                getline(cin , category);
                                tracker.searchByCategory(category);
                            }
                            else if (myOption == 3) {
                                cout << endl << endl;
                                break;
                            }
                            else {
                                cout << "Invalid option!" << endl << endl;
                            }
                        }
                    }
                    else if (option == 5) {
                        cout << endl << endl;
                        tracker.viewExpenses();
                        cout << "Enter Expense ID to edit: ";
                        int ID;
                        cin >> ID;
                        tracker.editExpense(ID);
                    }
                    else if (option == 6) {
                        cout << endl << endl;
                        tracker.finalReportGenerate();

                    }
                    else if (option == 7) {
                        cout << endl << endl;
                        break;
                    }
                    else {
                        cout << "invalid option." << endl << endl;
                    }
                }
            }
            else if (choice == 2) {
                registration();
            }
            else if (choice == 3) {
                break;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }

    }
    void registration() {
        cout << endl << endl;
        while (true) {
            cout << "choose an option number:" << endl;
            cout << "1. Create Account \n";
            cout << "2. Account Already Exists \n";
            cout << "3. Exit \n";
            int choice;
            cin >> choice;
            if (choice == 1) {
                cout << endl << endl;
                users.signUp();

            }
            else if (choice == 2) {
                cout << endl << endl;
                users.logIn();
            }
            else if (choice == 3) {
                cout << endl << endl;
                break;
            }
            else {
                cout << "invalid choice." << endl;
            }
        }


    }
};


int main() {
    UI ui;
    ui.run();
    return 0;
}




