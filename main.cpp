// Skriven av Tommy Yasi/toya1800 2019-01-11
// Project, main.cpp

#include "project.h"
#include <iostream>

int main() {
    vector<Person> persons;
    // Huvudmeny
    bool repeat = true;
    do{
        menu();
        char ch;
        cin >> ch;
        cin.get(); // Töm Enter
        // Meny alternativ
        switch(ch){
            case '1': add_person(persons);
                break;
            case '2': print_list(persons);
                break;
            case '3': search_person(persons);
                break;
            case '4': delete_person(persons);
                break;
            case '5': perform_sort(persons);
                break;
            case '6': save_to_file(persons);
                break;
            case '7': read_from_file(persons);
                break;
            case 'q':
            case 'Q': repeat = false;
                break;
            default: cout << "Invalid input, please try again." << endl;
        }
    } while(repeat); // Fortsätt så länge ch != Q/q

    return 0;
}

