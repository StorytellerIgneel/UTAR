#pragma once
#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "headers.hpp"

string  banner                  (string to_print);
void    notification            (string notification);
void    display_user_details    (user   patient, bool    registration);
void    menu                    (user   patient, admin target_admin, string stage, string content, string prompt, bool display_details, string file);

//Return a string where to_print is at the center of output (terminal width)
string  banner(string to_print)
{
    string  whitespace((TERMINAL_WIDTH-to_print.length())/2, ' ');
    return  (whitespace + to_print + whitespace + "\n");
}

//Clear the console screen and display a notification message, with a banner
void    notification(string notification)
{   
    string  modified_notification;
    size_t  newline_count;
    size_t  index;
    int     newline_pos;

    index = 0;
    newline_count = count(notification.begin(), notification.end(), '\\');
    if (newline_count != 0) // newline present inside message
    {
        for (int i = 0; i <= newline_count; i++)
        {
            newline_pos = notification.find('\\', index);
            modified_notification += notification.substr(index, newline_pos - index) + "\n";
            index = newline_pos + 1;
        }
    }
    else // no newline
        modified_notification = notification;
    system("cls");
    cout << LINE << endl
         << banner("Notification")
         << LINE << endl << endl
         << modified_notification << endl << endl << LINE;
    return;
}

//display user details within the content area of the menu template
void    display_user_details(user   patient, bool    registration = false)
{
    cout << "Name\t\t: " << patient.details.name << endl
        << "Age\t\t: " << patient.details.age << endl
        << "Phone number\t: " << patient.details.phone_number << endl
        << "Home address\t: " << patient.details.home_address << endl;
    if (registration == true)
    {
        cout << "Username\t: " << patient.access.username << endl
            << "Password\t: " << patient.access.password << endl << endl;
    }
    return;
}

//display a template with the banner, time, user status, content and prompts 
//dual-sided enabled for both user and admin, differs mainly in user status and show the current viewing patient for admin
void    menu(user   patient, admin target_admin, string stage, string content, string prompt = "", bool display_details = false, string file = "") //for selections
{
    string      username;
    string      patient_name;
    string      line;
    string      current_time_str;
    time_t      current_time;

    current_time = time(nullptr);
    current_time_str = ctime(&current_time);
    current_time_str.pop_back();

    system("cls");
    cout << LINE    
         << banner(stage)
         << LINE;

    if (target_admin.admin_name != "") // admin using
    {
        username = "Admin: " + target_admin.admin_name;
        if (patient.details.name != "") // admin using and for a patient.
            patient_name = "Viewing Patient: " + patient.details.name;
        else // admin using but not for patient yet
            patient_name = "";
    }
    else if (target_admin.admin_name == "" && patient.access.username != "") // user is using
        username = "User: " + patient.access.username;
    else //guest mode
        username = "Guest";

    cout << left << username << right << setw(TERMINAL_WIDTH - username.length()) << current_time_str << endl;

    if (patient_name != "")
        cout << patient_name << endl;
    cout << LINE << endl;
    if(display_details == 1)
        display_user_details(patient, true);
    if (file == "")
    {
        cout << content << endl << endl << "(Press Ctrl + Z together and enter to quit)" << endl
         << LINE
         << prompt;
    }
    else
    {
        ifstream    print_file(file, ios::in);

        cout << content << endl << endl;
        while(getline(print_file, line))
        {
            cout << line.substr(0, line.length() - 1);  // to skip the '\' or '/' sign 
            if (line[line.length() - 1] == '\\' || line[line.length() - 1] == '/')
                cout << endl;
        }
        cout << endl << LINE << prompt;
        print_file.close();
    }
    return;
}

#endif