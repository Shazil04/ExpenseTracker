#include <iostream>
using namespace std;
class Expense {
    private:int ID ;
    private:string date;
    private:string category;
    private:double amount;
    private:string note;

    Expense(int ID , const string& date , const string &category , double amount , const string & note){
        this->ID = ID;
        this->date = date;
        this->category = category;
        this->amount = amount;
        this->note = note;
    }
    public:void setAmount(double myAmount) {
        if (myAmount < 0) {
            cout << "Invalid Amount " << myAmount << endl;
        }
        else {
            amount = myAmount;
        }
    }
    public:string getCategory() {
        return category;
    }
    public:double getAmount() const {
        return amount;
    }
    public:void getDate(string &myDate) const {
        myDate = date;
    }
};



int main() {

    cout << "Expense Tracker Project Initialized!" << endl;
    return 0;
}
