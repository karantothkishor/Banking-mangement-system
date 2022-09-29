
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

class bank_acc
{
public:
    long acc_num;
    string fname, lname;
    float balance = 0;
    float amount;
    float depo;
    long mobile_num;
    int pin;
    static long next_acc_num;

    create_acc();
    display_acc_details();
    deposit_money();
    withdraw_money();
    modify_acc_details();
    delete_acc();
    friend ofstream &operator<<(ofstream &ofs, bank_acc &account);
    friend ifstream &operator>>(ifstream &ifs, bank_acc &account);
    friend ostream &operator<<(ostream &os, bank_acc &account);
};
long bank_acc ::next_acc_num = 0;
bank_acc ::create_acc()
{
    int pin_check;
    cout << "Enter your first name : ";
    cin >> fname;
    cout << endl;
    cout << "Enter your last name : ";
    cin >> lname;
    cout << endl;
    cout << "Enter your mobile number : ";
    cin >> mobile_num;
    cout << endl;
    fflush(stdin);
set_pin:
    cout << "Set a 4 digit pin as security pin(note : all values should be integers) : ";
    cin >> pin;
    cout << endl;
    cout << "Re-enter and Confirm pin : ";
    cin >> pin_check;
    cout << endl;

    if (pin != pin_check)
    {
        cout << "Both pins did'nt match. Try again " << endl;
        goto set_pin;
    }
deposit:
    cout << "Enter money to deposit : ";
    cin >> depo;
    cout << endl;
    if (depo < 500)
    {
        cout << "Minimum Balance should be 500. Deposit amount more than 500. " << endl;
        goto deposit;
    }
    else
        balance += depo;
    acc_num = ++next_acc_num;

    // system("cls");
    // Sleep(2000);
    cout << "\t\t\t\t\tCONGRATULATIONS!!! \n\n\t YOUR ACCOUNT IS SUCCESFULLY CREATED....\n\n"
         << endl;

    cout << "\tYour account details : " << endl;
}
ofstream &operator<<(ofstream &ofs, bank_acc &account)
{
    ofs << account.acc_num << endl;
    ofs << account.fname << endl;
    ofs << account.lname << endl;
    ofs << account.balance << endl;
    ofs << account.mobile_num << endl;
    ofs << account.pin << endl;
    return ofs;
}
ifstream &operator>>(ifstream &ifs, bank_acc &account)
{
    ifs >> account.acc_num;
    ifs >> account.fname;
    ifs >> account.lname;
    ifs >> account.balance;
    ifs >> account.mobile_num;
    ifs >> account.pin;
    return ifs;
}
ostream &operator<<(ostream &os, bank_acc &account)
{
    os << "\n\t \t First Name : " << account.fname << endl;
    os << "\t \t Last Name : " << account.lname << endl;
    os << "\t \t Account Number : " << account.acc_num << endl;
    os << "\t \t Current Balance : " << account.balance << endl;

    // os << "\t \t Mobile Number : " << account.mobile_num << endl;
    return os;
}
void replace_pin(int acc_no, int new_pin)
{
    bank_acc Acc;
    ifstream fin;
    fin.open("user_data.data");
    ofstream fout;
    fout.open("temp.data");
    while (!fin.eof())
    {
        fin >> Acc;
        cout << Acc << endl;
        if (Acc.acc_num == acc_no)
        {
            Acc.pin = new_pin;
            fout << Acc << endl;
        }
        else
            fout << Acc << endl;
    }

    fin.close();
    fout.close();
    // char filename[] = "user_data.data";
    // int res = remove(filename);
    // cout << res << endl ;
    // rename("temp.data", "user_data.data");
}
void new_user()
{
    bank_acc new_acc;
    int choice;
    // system("cls");
    cout << "\n \t \t \t \t \t HELLO....\n"
         << endl;
    // Sleep(2000);
    cout << "\t MENU:\n"
         << endl;
    cout << "\t 1.Create New Account" << endl;
    cout << "\t 2.Exit\n"
         << endl;
select:
    cout << "Enter your choice:";
    cin >> choice;
    // system("cls");
    switch (choice)
    {
    case 1:
    {
        cout << "Please enter your details to continue :\n"
             << endl;
        new_acc.create_acc();
        ofstream outfile;
        outfile.open("user_data.data", std::ios_base::app);
        outfile << new_acc << endl;
        outfile.close();
        cout << new_acc << endl;
        break;
    }
    case 2:
    {
        exit(0);
        break;
    }
    default:
    {
        cout << "\tInvalid option. Select a valid one. \n";
        goto select;
    }
    }
}
void existing_user()
{
    bank_acc Account;
    long acc_no;
retry:
    cout << "Enter your account number : ";
    cin >> acc_no;
    ifstream infile;
    infile.open("user_data.data");
    if (!infile)
    {
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
    }
    bool acc_found = false;
    while (!infile.eof())
    {
        infile >> Account;
        if (Account.acc_num == acc_no)
        {
            acc_found = true;
            break;
        }
    }
    if (acc_found == false)
    {
        cout << "No account found. \n Retry";
        goto retry;
    }
    int user_pin;
    cout << "Enter your pin to continue : ";
    cin >> user_pin;
    if (user_pin == Account.pin)
    {
        cout << "Welcome back";
        int choice;
    user:
        // system("cls");
        // Sleep(2000);
        cout << "\t MENU:\n"
             << endl;
        cout << "\t 1. Balance Enquiry" << endl;
        cout << "\t 2. Deposit money" << endl;
        cout << "\t 3. Withdraw money" << endl;
        cout << "\t 4. Update your details" << endl;
        cout << "\t 5. Update your pin" << endl;
        cout << "\t 6. Exit\n"
             << endl;
    select:
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Your account balance is : " << Account.balance << endl;
            goto user;
            break;
        }
        case 2:
        {
            long amount = 0;
            cout << "Enter amount to deposit : ";
            cin >> amount;
            Account.balance += amount;
            cout << "Your current balance is : " << Account.balance << endl;
            goto user;
            break;
        }
        case 3:
        {
            long amount = 0;
            cout << "Enter amount to withdraw : ";
            cin >> amount;
            Account.balance -= amount;
            cout << "Your current balance is : " << Account.balance << endl;
            goto user;
            break;
        }
        case 4:
        {
            // system("cls");
            // Sleep(2000);
            cout << "\t What you want to update :\n"
                 << endl;
            cout << "\t 1. First Name" << endl;
            cout << "\t 2. Last Name" << endl;
            cout << "\t 3. Mobile Number " << endl;
            cout << "\t 4. Exit\n"
                 << endl;
        update:
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                cout << "Enter your new first name : " << endl;
                string new_fname;
                cin >> new_fname;
                Account.fname = new_fname;
                cout << "Your details updated successfully." << endl;
                goto update;
                break;
            }
            case 2:
            {
                cout << "Enter your new last name : " << endl;
                string new_lname;
                cin >> new_lname;
                Account.lname = new_lname;
                cout << "Your details updated successfully." << endl;
                goto update;
                break;
            }
            case 3:
            {
                cout << "Enter your new mobile number : " << endl;
                long new_mobilenumber;
                cin >> new_mobilenumber;
                Account.mobile_num = new_mobilenumber;
                cout << "Your details updated successfully." << endl;
                goto update;
                break;
            }
            case 4:
            {
                exit(0);
                break;
            }
            default:
            {
                cout << "\tInvalid option. Select a valid one. \n";
                goto update;
            }
            }
        }
        case 5:
        {
            char c;
            int old_pin;
        yesorno:
            cout << "Are you sure to change your pin? \n press y for yes, n for no\n (y/n) : ";
            cin >> c;
            if (c == 'y' || c == 'Y')
            {
            pin:
                cout << "Enter your old pin : ";
                cin >> old_pin;
                if (old_pin == Account.pin)
                {
                    int new_pin;
                    cout << "Enter new pin : ";
                    cin >> new_pin;
                    replace_pin(acc_no, new_pin);
                    cout << "Your pin updated successfully." << endl;
                    infile.close();
                    int res = remove("user_data.data");
                
                    rename("temp.data", "user_data.data");
                }
                else
                {
                    cout << "Incorrect pin entered.\nTry again." << endl;
                    goto pin;
                }
            }
            else if (c == 'n' || c == 'N')
            {
                goto user;
            }
            else
            {
                cout << "Invalid input.\nTry again" << endl;
                goto yesorno;
            }
            break;
        }
        case 6:
        {
            exit(0);
            break;
        }
        default:
        {
            cout << "\tInvalid option. Select a valid one. \n";
            goto user;
        }
        }
    }
    // infile.close();
    // int res = remove("user_data.data");
    // cout <<  "hi" << res << endl;
    
}

int main()
{
    // system("cls");
    // Sleep(2000);
    cout << " \n \t \t \t \t \t WELCOME!!! \n"
         << endl;
    // Sleep(2000);

    int choice;

begin:
    // system("cls");
    cout << "\t Please select one of the options below :  \n"
         << endl;

    cout << "\t 1. New User" << endl;
    cout << "\t 2. Existing User" << endl;
    cout << "\t 3. Exit out of process" << endl;
select:
    cout << "\n\t Enter your choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        new_user();
        break;
    case 2:
        existing_user();
        break;
    case 3:
        exit(0);
    default:
        cout << "\tInvalid option. Select a valid one. \n";
        goto select;
    }
}
