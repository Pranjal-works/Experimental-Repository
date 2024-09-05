#include<iostream>
#include<fstream>
#include "Header_files/execution.h"
using namespace std;

void check_validate(int role_choice);

int main()
{
    int role_choice;

    while(1)
    {
    cout << "\n\n********************Welcome********************\n\n";
    cout << "Choose your ROLE\n";
    cout << "1.Receptionist\n2.Manager\n3.Chef team\n4.Exit\n";
    cin >> role_choice;
    if(role_choice == 4)
    {
        exit(0);
    }
    else
    {
        check_validate(role_choice);
    }
    }
    cout << "Logged out\n";
    return 0;
}

void check_validate(int role_choice)
{

    string password;
    cout << "Enter your password to login : ";
    cin >> password;
    ifstream fin("passwords.txt");
    if(!fin)
    {
        cout << "Error opening the password file\n";
        return;
    }
    if(role_choice == 1)
    {
        string receptionist_password;
    fin >> receptionist_password;
    if(password != receptionist_password)
    {
        return;
    }
        cout << "Authorization done successfully!\n";
        Receptionist r1;
        r1.show_availability();
        if(r1.book_room())
        {
            r1.get_cust_data();
            r1.print_recipt();
        }
    }
    else if(role_choice == 2)
    {
        string manager_password;
        getline(fin,manager_password);
        getline(fin,manager_password);
    if(password != manager_password)
    {
        return;
    }
        cout << "Authorization done successfully!\n";
        int choice;
        Manager m1;
        while(1)
        {
            cout << "1.View staff details\n2.Add a staff\n3.Exit";
            cin >> choice;
            switch(choice)
            {
                case 1: m1.get_staff_data();break;
                case 2: m1.add_staff();break;
                case 3: exit(0);break;
            }
        }
    }
    else if(role_choice == 3)
    {
        string chef_team_password;
        fin >> chef_team_password;
        if(password != chef_team_password)
        {
            return;
        }
        cout << "Authorization done successfully!\n";
    }
}
