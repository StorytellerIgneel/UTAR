#pragma once
#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include "headers.hpp"
#include "template.hpp"
#define ALL_PRESENT 0
#define MISSING     1
#define ERROR       2 //technically can be any number other than 0 and 1
//defined global variables to 

bool    is_number(string  target, int    *converted)
{
    for (char c : target)
    {
        if (!isdigit(c))
            return false;
    }
    *converted = stoi(target);
    return true;
}

bool    is_double(string  target, double    *converted)
{
    int dot;

    dot = 0;
    for (char current_char : target)
    {
        if (!isdigit(current_char))
        {
            if (current_char == '.' && dot == 0) // only allow 1 dot to be in the double variable
                dot += 1;
            return false;
        }
    }
    *converted = stod(target);
    return true;
}

string  remove_trail(string input)
{
    if(isspace(input[input.length() - 1]))
        return (input.substr(0, input.length() - 1));
    else
        return input;
}

void    success_message(unsigned int success_code, string username = "")
{
    string          success_message;
    unsigned int    current_line = 1;
    ifstream        in_file("success_message.txt");

    cout << "\n";
    while(current_line <= success_code)
    {
        getline(in_file, success_message);
        current_line++;
    }
    if (username != "")
        success_message += username;
    notification(success_message);
    cout << "\nPress enter to contine";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    in_file.close();
    return;
}

void error_message(unsigned int error_code, string missing_file = "")
{
    string          error_message;
    string          input_dummy;
    ifstream        in_file("error_message.txt");
    unsigned int    current_line = 1;

    cin.clear();
    cout << "\n";
    while(current_line <= error_code)
    {
        getline(in_file, error_message);
        current_line++;
    }
    if (missing_file != "")
        error_message = missing_file + error_message;
    notification(error_message);
    cout << "\nPress enter to contine.";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    in_file.close();
    return;
}

int     check_file_present()
{
   string          file_list[]         = 
   {"SMBG_recommendation.txt", 
    "admin.txt", 
    "clinic_followup_treatment.txt", 
    "control_targets.txt", 
    "error_message.txt", 
    "glucose_lowering_agents.txt", 
    "hba1c_less_tight.txt", 
    "hba1c_tight.txt", 
    "individualised_hba1c_target.txt", 
    "medication_guide.txt", 
    "success_message.txt", 
    "newly_diagnosed_treatment.txt", 
    "principle_recommend.txt", 
    "t2dm_management.txt", 
    "user_access.txt", 
    "user_details.txt", 
    "user_meal_record.txt", 
    "user_medical.txt", 
    "user_medical_report.txt"};

    for(int    file_list_counter   = 0; file_list_counter < 19; file_list_counter++)
    {
        ifstream    in_file(file_list[file_list_counter], ios::in);
        if(!in_file)
        {
            if (file_list[file_list_counter] == "error_message.txt")
            {
                cout << "The error message file is missing.\nPlease ensure that all files are in the current working directory before using this system.";
                cin.get();
                return MISSING;
            }
            error_message(3, file_list[file_list_counter]);
            return MISSING;
        }
        else
            in_file.close();
    }
    return ALL_PRESENT;
}

int exit_check(istream *cin)
{
    if (!(*cin))
    {
        (*cin).clear();
        return 1;
    }
    else
        return 0;
}

#endif