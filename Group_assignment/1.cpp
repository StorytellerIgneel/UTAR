#include "headers.hpp"
#include "validation.hpp"
#include "access_control.hpp"
#include "file_handling.hpp"

/*
Act as the initial starter of the entire programme (main) and as the initial access control.
Pre:
i.  libary "headers.hpp" is included
ii. libary "validation.hpp" is included
iii. libary "access_control.hpp" is included
iv. libary "file_handling.hpp" is included
*/

int main(void) //initial access control
{
    int     user_count;
    int  choice;
    user    dummy;
    user    user_list[MAX_CAPACITY];
    map < int, function < void(user[], int) >> option_list;
    option_list[1] = login;
    option_list[2] = registration_control;

    read_user_data(user_list, MAX_CAPACITY);
    while(1)
    {
        user_count   = 0;
        while(user_list[user_count].details.name != "")
            user_count++;
        menu(dummy, "LOGIN", "Welcome to Diabetes Management System!\nPlease choose to login or to register:\n1. Login\n2. Register\n3. Exit System", "Enter choice: ");
        cin >> choice;
        if (cin.fail())
            error_message(1);
        else if (choice == 1 || choice == 2)
            option_list[choice](user_list, user_count);  // Call the selected function
        else if (choice == 3)
        {
            export_user_data(user_list, user_count);
            exit(0);
        }
        else
        {
            error_message(2);
            cin.clear();
            cin.ignore();
        }
            
    }
    return 0;
}