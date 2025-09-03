#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

class Expense {
private:
    int ID ;
    string date;
    string category;
    double amount;
    string note;
    string owner;

public:
    Expense(int ID , const string& date , const string &category , double amount , const string & note , const string &owner){
        this->ID = ID;
        this->date = date;
        this->category = category;
        this->amount = amount;
        this->note = note;
        this->owner = owner;
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
    string getOwner()const {
        return owner;
    }
    void display() const {


             cout << left << setw(5) << ID
             << left << setw(15) << date
             << left << setw(15) << category
             << left << setw(10) << fixed << setprecision(2) << amount
             << left << setw(20) << note
             << endl;
    }

};

class ExpensesTracker {
    vector<Expense> expenses;
    int nxtID = 0;

public:
    static bool equalIgnoreCase2(const string &a , const string &b) {
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


    void addExpense(const string &currentUser){
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

        Expense e1(newID, newDate, newCategory, newAmount, newNote , currentUser);
        expenses.push_back(e1);
        saveToFile();
        cout << "Expense added successfully!\n\n\n";
    }


    void viewExpenses(const string &currentUser) const {
        cout << "=======================================================" << endl
        << "                  ===================" << endl
        << "                  |   ALL  EXPENSES  |" << endl
        << "                  ===================" << endl
        << left << setw(5) << "ID"
        << left << setw(15)<< "Date"
        << left << setw(15) << "Category"
        << left << setw(10) << "Amount"
        << left << setw(20) << "Note"
        << endl ;
        for (const Expense &e : expenses){
            if (e.getOwner() == currentUser) {
                e.display();
            }
        }
        cout << "\n====================================================" << endl;
    }


    void searchByDate(const string &currentUser , const string &userDate)const{
        bool found = false;
        cout << "\n=======================================================" << endl
        << "        All expenses for your selected date: " << endl
        << "=======================================================" << endl
        << left << setw(5) << "ID"
        << left << setw(15)<< "Date"
        << left << setw(15) << "Category"
        << left << setw(10) << "Amount"
        << left << setw(20) << "Note"
        << endl << endl;
        for (const Expense &e : expenses){
            if ( e.getOwner() == currentUser && e.getDate() == userDate) {
                e.display();
                found = true;
            }
        }
        if (!found) {
            cout << "Not found: Expense not found" << endl;
        }
        cout << "\n=======================================================" << endl;
    }


    void searchByCategory(const string &currentUser , const string &userCategory)const{
        bool found = false;
        cout << "\n=======================================================" << endl
        << "       All expenses for your selected category: " << endl
        << "=======================================================" << endl
        << left << setw(5) << "ID"
        << left << setw(15)<< "Date"
        << left << setw(15) << "Category"
        << left << setw(10) << "Amount"
        << left << setw(20) << "Note"
        << endl << endl;
        for (const Expense &e : expenses){
            if (equalIgnoreCase2(userCategory , e.getCategory()) && e.getOwner() == currentUser) {
                e.display();
                found = true;
            }
        }
        if (!found){
            cout << "Not found: Expense not found" << endl;
        }
        cout << "\n=======================================================" << endl;
    }


    void deleteExpense(const int ID , const string &currentUser){
        for (auto it = expenses.begin(); it != expenses.end(); ++it){
            if (it->getID() == ID && it->getOwner() == currentUser) {
                expenses.erase(it);
                cout << "Expense with ID " << ID << " deleted." << endl;
                saveToFile();
                return;


            }
        }
        cout << "Expense with ID " << ID << " not found." << endl;
    }


    void editExpense(const int ID , const string &currentUser) {
        for (Expense &e : expenses) {
            if (e.getID()== ID && e.getOwner() == currentUser) {
                cout << "\n=======================================================" << endl;
                e.display();
                cout << "======================================================" << endl;
                while (true) {
                    cout << "\nWhat do you want to edit: " << endl;
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
                        cout << "Expense with ID " << ID << " edited." ;
                        cout << "\n=======================================================" << endl;
                        e.display();
                        cout << "======================================================" << endl;
                    } else if (choice == 2) {
                        cout << "Enter Category " << endl;
                        string newCategory;
                        getline(cin, newCategory);
                        e.setCategory(newCategory);
                        cout << "Expense with ID " << ID << " edited."
                        << "\n=======================================================" << endl;
                        e.display();
                        cout << "======================================================" << endl;
                    } else if (choice == 3) {
                        cout << "Enter Amount " << endl;
                        double newAmount;
                        cin >> newAmount;
                        cin.ignore();
                        e.setAmount(newAmount);
                        cout << "Expense with ID " << ID << " edited."
                        << "\n=======================================================" << endl;
                        e.display();
                        cout << "======================================================" << endl;
                    } else if (choice == 4) {
                        cout << "Enter Note " << endl;
                        string newNote;
                        getline(cin, newNote);
                        e.setNote(newNote);
                        saveToFile();
                        cout << "Expense with ID " << ID << " edited."
                        << "\n=======================================================" << endl;
                        e.display();
                        cout << "======================================================" << endl;
                    } else if (choice == 5) {
                        break;
                    } else {
                        cout << "Invalid choice." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            }
        }
    }
    void saveToFile() const{
        ofstream write ("Record.txt" , ios::out);
        if (!write.is_open()) {
            cout << "Cannot open file." << endl;
            return;
        }
        for (const Expense &e : expenses) {
            write << e.getID() << ",";
            write << e.getOwner() << ",";
            write << e.getDate() << ",";
            write << e.getCategory() << ",";
            write << e.getAmount() << ",";
            write << e.getNote() << endl;
        }
        write.close();

    }
    void loadFromFile() {
        ifstream read("Record.txt", ios::in);
        if (!read.is_open()) {
            cout << "Cannot open file." << endl;
            return;
        }

        string line;
        int maxID = 0;

        while (getline(read, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string id, owner, date, category, amountStr, note;

            if (!getline(ss, id, ',')) continue;
            if (!getline(ss, owner, ',')) continue;
            if (!getline(ss, date, ',')) continue;
            if (!getline(ss, category, ',')) continue;
            if (!getline(ss, amountStr, ',')) continue;
            if (!getline(ss, note)) note = "";

            try {
                int ID = stoi(id);

                // trim spaces if needed
                amountStr.erase(remove_if(amountStr.begin(), amountStr.end(), ::isspace), amountStr.end());
                double Amount = stod(amountStr);

                Expense e(ID, date, category, Amount, note, owner);
                maxID = max(maxID, ID);
                expenses.push_back(e);
            }
            catch (const exception &) {
                cerr << "Skipping bad line: " << line << endl;
                continue;
            }
        }

        nxtID = maxID;
        read.close();
    }

    void finalReportGenerate(const string &currentUser) const{
        double totalAmount = 0;
        vector<string> categories = {"Food" , "Transport" , "Entertainment", "Studies", "Debts", "Shopping" , "Medical" , "Others"};
        vector<double> categoriesTotal(categories.size(), 0.0);
        vector<double> percentages(categories.size(), 0.0);
        for (const Expense &e : expenses) {
            if (e.getOwner() != currentUser) continue;
            totalAmount += e.getAmount();
            for (int i = 0 ; i < categories.size(); i++) {
                if (equalIgnoreCase2(categories[i] , e.getCategory())) {
                    categoriesTotal[i] += e.getAmount();

                    break;
                }
            }
        }
        for (int i = 0; i < categories.size(); i++) {
            if (totalAmount > 0) {
                percentages[i] = (categoriesTotal[i] / totalAmount) * 100.0;
            } else {
                percentages[i] = 0.0;
            }
        }
        string expensive = myExpensiveCategory(currentUser);
        string cheapest = myCheapestCategory(currentUser);

        cout << "======================================================" << endl
        << "                  ===================" << endl
        << "                  | EXPENSE REPORT  |" << endl
        << "                  ===================" << endl
        << "\nCategories Breakdown:" << endl
        << "=====================" << endl
        << "=====================================================" << endl
        << left << setw(20) <<  "Category" << left  << setw(20) << "Expense" << "Percentage" << endl
        << "=====================================================" << endl ;
        for (int i = 0; i < categories.size(); i++) {
            cout << left << setw(20) <<  categories[i] << left  << setw(20) << fixed << setprecision(2) <<  categoriesTotal[i] << fixed << setprecision(2) << percentages[i] << "%" << endl;
        }
        cout << "=====================================================" << endl
        << "Summary:" << endl
        << "========" << endl
        << "*> Total Expenses = " << fixed << setprecision(2) << totalAmount << endl
        << "*> Most Expensive Category = "  << expensive << endl
        << "*> Most Cheapest Category = "  << cheapest << endl
        << "======================================================" << endl << endl ;
    }
    void showSingleExpense(int a , const string &currentUser) const {
        for (const Expense &e : expenses) {
            if (a == e.getID() && e.getOwner() == currentUser) {
                e.display();
                return;
            }
        }
        cout << "Expense with ID = " << a << " not found" << endl;
    }
    string myExpensiveCategory(const string &currentUser) const {
        double amount  = INT_MIN;
        string myCategory ;
        for (const Expense &e : expenses) {
            if (e.getOwner() != currentUser) continue;
            if (e.getAmount() > amount) {
                myCategory = e.getCategory();
                amount = e.getAmount();
            }
        }
        return myCategory;
    }

    string myCheapestCategory(const string &currentUser) const {
        double amount  = INT_MAX;
        string myCategory ;
        for (const Expense &e : expenses){
            if (e.getOwner() != currentUser) continue;
            if (e.getAmount() < amount && e.getAmount() > 0) {
                myCategory = e.getCategory();
                amount = e.getAmount();
            }
        }
        return myCategory;
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
        getline(cin, username);
        if (username.empty()) {
            cout << "Username cannot be empty." << endl;
            return;
        }
        for (const User &myUser : users) {
            if (equalIgnoreCase(myUser.getUsername() , username)) {
                cout << "User already exists." << endl;
                return;
            }
        }
        cout << "Enter password: ";
        string password;
        getline(cin, password);
        if (password.empty()) {
            cout << "Password cannot be empty." << endl;
            return;
        }
        cout << "confirm password: ";
        string confirmPassword;
        getline(cin , confirmPassword);
        if (password == confirmPassword) {
            users.emplace_back(username, password);
            cout << "User created successfully!" << endl;
        }
        else {
            cout << "Password didn't match!" << endl;
        }

    }
    string  logIn() const {
        int counter = 1;


        while (counter <= 5) {
            cout << "Enter username: ";
            string username;
            getline(cin, username);

            if (username.empty()) {
                cout << "Username cannot be empty." << endl;
                return "";
            }
            const User* foundUser = nullptr;
            for (const User &myUser : users) {
                if (username == myUser.getUsername()) {
                    foundUser = &myUser;
                    break;
                }
            }
            if (!foundUser){
                cout << "Wrong Username! " << endl;
            } else {
                cout << "Enter password: ";
                string password;
                getline(cin, password);

                if (password == foundUser->getPassword()) {
                    cout << "Logged in successfully!" << endl;
                    cout << "Welcome " << username << "!" << endl << endl;
                    return username;
                } else {
                    cout << "Wrong Password!" << endl;
                }
            }

            cout << "Login failed! Try again.\n";
            cout << "Attempts left: " << 5 - counter << endl;
            counter++;
        }
            cout << "No attempt left, try again in 30 minutes!" << endl;
            return "";
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
    string currentUser;

public:
    UI(){
        cout << "=============================\n";
        cout << "         EXPENSE TRACKER       \n";
        cout << "=============================\n\n";
        tracker.loadFromFile();
        users.loadFromFile();
    }
    ~UI(){
        cout << "============================================\n"
        << "      THANKS FOR USING EXPENSE TRACKING \n"
        << "============================================\n";

    }
    void run() {
        while (true) {
            cout << "choose an option number:" << endl;
            cout << "1. Main Menu \n";
            cout << "2. Register yourself\n";
            cout << "3. Exit\n";
            int choice;
            cin >> choice;
            cin.ignore();
            if (choice == 1) {
                if (currentUser.empty()) {
                    cout << "Please log in first!\n";
                    continue;
                }
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
                    cin.ignore();
                    if (option == 1) {
                        tracker.addExpense(currentUser);
                    }
                    else if (option == 2) {
                        cout << endl << endl;
                        tracker.viewExpenses(currentUser);
                        cout << "Enter Expense ID to delete: ";
                        int ID;
                        cin >> ID;
                        if (ID <= 0) {
                            cout << "Invalid ID.\n";
                        }
                        else {
                            cout << endl << endl;
                            cout << "Are you sure to delete expense with ID = " << ID << ": (Y/N)" << endl;
                            tracker.showSingleExpense(ID , currentUser);
                            string c;
                            cin >> c;
                            if (UserManager::equalIgnoreCase(c , "y")) {
                                tracker.deleteExpense(ID , currentUser);
                                tracker.saveToFile();
                            }
                        }

                    }
                    else if (option == 3) {
                        cout << endl << endl;
                        tracker.viewExpenses(currentUser);
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
                            cin.ignore();
                            if (myOption == 1) {
                                cout << "Enter Date to search:" << endl;
                                string date;
                                getline(cin , date);
                                tracker.searchByDate( currentUser , date);
                            }
                            else if (myOption == 2) {
                                cout << "Enter Category to search:" << endl;
                                string category;
                                getline(cin , category);
                                tracker.searchByCategory( currentUser , category );
                                cout << endl << endl;
                            }
                            else if (myOption == 3) {
                                cout << endl << endl;
                                break;
                            }
                            else {
                                cout << "Invalid option!" << endl << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            }
                        }
                    }
                    else if (option == 5) {
                        cout << endl << endl;
                        tracker.viewExpenses(currentUser);
                        cout << "Enter Expense ID to edit: ";
                        int ID;
                        cin >> ID;
                        tracker.editExpense(ID , currentUser);
                    }
                    else if (option == 6) {
                        cout << endl << endl;
                        tracker.finalReportGenerate(currentUser);

                    }
                    else if (option == 7) {
                        cout << endl << endl;
                        break;
                    }
                    else {
                        cout << "invalid option." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            cin.ignore();
            if (choice == 1) {
                cout << endl << endl;
                users.signUp();
                users.saveToFile();

            }
            else if (choice == 2) {
                cout << endl << endl;
                string loggedIn = users.logIn();
                if (!loggedIn.empty()) {
                    currentUser = loggedIn;
                }
            }
            else if (choice == 3) {
                cout << endl << endl;
                break;
            }
            else {
                cout << "invalid choice." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
};


int main() {
    UI ui;
    ui.run();
    return 0;
}




