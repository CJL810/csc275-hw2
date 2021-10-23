/*************************************************************************
** Author: Cameron Lomax
** Program: HW2, Q1
** Date Created: October 18, 2021
** Date Last Modified : October 22, 2021
** Usage: No command line arguments
** Problem:
- Define a check struct with apporiate data types and an overloaded 
operator which takes Check and a float variable to compare whether the 
CheckAmount is greater than the second variable. 
- Define a class called CheckBook
*************************************************************************/

#include<iostream>
#include<string>


using namespace std;

struct Check
{
    float CheckNum;
    string CheckMemo;
    float CheckAmount;

};

bool operator > (Check& check, float amount);

ostream& operator << (ostream& os, Check& check);

bool operator <= (Check& check, float amount);


//Checkbook class
class CheckBook {
    public:
        CheckBook(): balance(0), numOfChecks(0), checkBookSize(4){};
        CheckBook(int num): numOfChecks(0), checkBookSize(0){balance=num; chkPtr= new Check[checkBookSize];}
        ~CheckBook(){};
        Check *chkPtr;
        void lastDeposit();
        float const getBal() {return balance;}
        int const getNumChecks() {return numOfChecks;}
        int const getCheckBookSize() {return checkBookSize;}
        void doubleCheckBookSize();
        void deposit(int amount){balance+=amount;}
        bool writeCheck(Check c_amount);
        void const displayChecks();
        void setBal(float amount) {balance=amount;}
        void setNumChecks(int num) {numOfChecks=num;}
        void setCheckBookSize(int num) {checkBookSize=num;}
    private:
        float balance;
        int numOfChecks;
        int checkBookSize;
};

void checkTest(CheckBook checkBook, int bal);


int main() {
    int bal = 1000;
    CheckBook checkBook(bal);
    checkTest(checkBook,bal);

    return 0;
}

bool operator <= (Check& check, float amount) {
    if (check.CheckAmount <= amount)
    {
        return true;
    }
    return false;
}

bool operator > (Check& check, float amount) {
    if (check.CheckAmount > amount)
    {
        return true;
    }
    return false;
}

ostream& operator << (ostream& os, Check& check) {
    os << check.CheckNum << " " << check.CheckAmount << " " <<check.CheckMemo << endl;
    return os;
}

//updates and writes check
bool CheckBook::writeCheck(Check c_amount) {
    if (c_amount > balance)
    {
        return false;
    }
    else {
        const string randomMemo[6] = {"food truck", "baby shower", "shopping", "gas station", "haircut", "lawn care"};
        int randomNum = rand() % 6;
        c_amount.CheckMemo = randomMemo[randomNum];
        c_amount.CheckNum = numOfChecks + 1;
        chkPtr[numOfChecks] = c_amount;
        numOfChecks++;
        balance -= c_amount.CheckAmount;
    }
}

//displays check
void const CheckBook::displayChecks() {
    for (int i = numOfChecks; i > 0; i--)
    {
        cout<<chkPtr[i-1];
    }
}

//checks and double checkbook size
void checkTest(CheckBook checkBook, int bal) {
    cout<<"\n______________________________\n"<<endl;
    Check c_amount;
    c_amount.CheckAmount = 24;
    
    while (c_amount <= checkBook.getBal())
    {
        checkBook.setBal(bal);
        c_amount.CheckAmount = 235;
        checkBook.writeCheck(c_amount);
        checkBook.lastDeposit();
        cout<<checkBook.getBal()<<endl;
            
            if (checkBook.getCheckBookSize() / 2 == checkBook.getNumChecks())
            {
                checkBook.doubleCheckBookSize();
            }

        bal -= c_amount.CheckAmount;
    }
    cout<<"\n______________________________\n"<<endl;
    checkBook.displayChecks();
    cout<<"\n______________________________\n"<<endl;
}



void CheckBook::lastDeposit() {
    cout<<chkPtr[numOfChecks - 1];
}

void CheckBook::doubleCheckBookSize() {
    Check *ptr = new Check [2 * checkBookSize];
    for (int i = 0; i < numOfChecks; i++)
    {
        ptr[i]=chkPtr[i];
    }
    checkBookSize *= 2;
    delete [] chkPtr;
    chkPtr = ptr;
    cout<< "Check Book ordered"<<endl;
    
} 