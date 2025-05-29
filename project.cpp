// Funktionsdefinitioner
#include "project.h"
#include <iostream>

void menu() {
    cout << endl;
    cout << "MAIN MENU" << endl << endl;
    cout << "1: Input information for one person." << endl;
    cout << "2: Print the list." << endl;
    cout << "3: Search for a person in the list." << endl;
    cout << "4: Delete person from the list." << endl;
    cout << "5: Choose how to sort the list." << endl;
    cout << "6; Save to the file." << endl;
    cout << "7: Read list from the file." << endl;
    cout << "Q/q: to exit the program. " << endl;
}
void add_person(vector<Person> &persons) {
    do {
        Person tempPerson; //Skriv in information om personen

        cout << "Input information for a person. " << endl;
        cout << "First name: " << endl;
        getline(cin, tempPerson.firstName);

        cout << "Last name: " << endl;
        getline(cin, tempPerson.lastName);

        // Kontrollerar också att användaren inte skriver versaler
        do {
            cout << "Signature (yyyxxx): " << endl;
            cin >> tempPerson.signature;
            if (!check_signature(tempPerson.signature)){
                cout << "Only lowercase letters allowed!" << endl;
            }
        } while(!check_signature(tempPerson.signature));

        cout << "Height [M]: " << endl;
        cin >> tempPerson.height;
        cin.get(); // Rensa ENTER

        persons.push_back(tempPerson); // Lägger in informationen i vectorn
    } while(yes_no("One more person? (y/n): "));
}
bool check_signature(string &str) {
    bool signature = true;
    for(char i : str) {
        if(isupper(i)){ // Inte godkänd om en bokstav är en versal
            signature = false;
        }
    }
    return signature;
}
bool yes_no(const string &str) {
    cout << endl << endl;
    cout << str << endl;

    char ch;
    do {
        cin >> ch;
        cin.get();

        ch = static_cast<char>(toupper(ch));
    } while(! (ch=='Y' || ch=='N'));

    return (ch=='Y');
}
void print_list(vector<Person> &persons) {
    cout << endl << endl;
    int counter = 0;
    for(const auto &e: persons) { // Räknar antal personer i listan
        counter++;
    }
    cout << "-----NAME LIST-----" << endl;
    cout << "Number of persons in list: " << counter << endl;
    cout << left << setw(5) << "Nr" << setw(20) << "Sign" << setw(60) << "Name" << "Length [m]" << endl;

    int i = 0; // Nummer bredvid namn
    for(auto e: persons) {
        ++i;
        cout << left << fixed << setprecision(2);
        cout << setw(5) << to_string(i) + ".";
        cout << setw(20) << e.signature;
        cout << setw(40) << e.firstName +  " " +  e.lastName;
        cout << setw(30) << right <<  e.height << endl;

        if((i+1)%20 == 0){ // 20 personer åt gången visas
            if(!yes_no("Next page?")){
                break;
            }
        }
    }
}
void sort_list (vector<Person> &persons, Sort method) { // Sortera listan efter vad användaren har valt
    switch (method) {
        case Sort::lastName:
            sort(persons.begin(), persons.end(), compare_by_lastname);
            cout << "List has been sorted on last name!" << endl;
            break;
        case Sort::signature:
            sort(persons.begin(), persons.end(), [](Person &a, Person &b) {
                return a.signature < b.signature;
            });
            cout << "List has been sorted on signature!" << endl;
            break;
        case Sort::height:
            sort(persons.begin(), persons.end(), [](Person &a, Person &b) {
                return a.height < b.height;
            });
            cout << "List has been sorted on height!" << endl;
            break;
        case Sort::randomize:
            random_shuffle(persons.begin(), persons.end());
            cout <<"List has been sorted randomly!" << endl;
            break;
        default:
            cout << "Invalid input!" << endl;
    }
}
void perform_sort(vector<Person> &persons) {
    cout << endl << endl;
    cout << "1: Sort by last name." << endl;
    cout << "2: Sort by signature." << endl;
    cout << "3: Sort by height." << endl;
    cout << "4: Sort by randomizing." << endl;

    // Användaren matar in hur listan ska sorteras
    int user_input;
    cin >> user_input;
    cin.get();

    Sort method = static_cast<Sort>(user_input); // Ändra från int till Sort
    sort_list(persons, method); // Anrop av genomförandet av sorteringen
}
bool compare_by_lastname(const Person &a, const Person &b) {
    string name_a = a.lastName + " " + a.firstName;
    string name_b = b.lastName + " " + b.firstName;
    if(a.lastName == b.lastName) { // Om efternamnen är lika så jämförs förnamnen
        name_a = a.firstName + " " + a.lastName;
        name_b = b.firstName + " " + b.lastName;
        return name_a < name_b;
    }
    return name_a < name_b;
}
void save_to_file(vector<Person> &persons) {
    ofstream outFile(name_file()); // Filen öppnas
    for(auto e : persons) {
        outFile << e.firstName << DELIM
                << e.lastName << DELIM
                << e.signature << DELIM
                << e.height << endl;
    }
    persons.clear();
    outFile.close();
}
string name_file() {
    string fileName;
    cout << "Give the file a name." << endl;
    cin >> fileName;
    cin.get();

    return fileName;
}
void read_from_file(vector<Person> &persons) {
    // Öppna och läs från filen
    ifstream inFile(name_file()); // Läser in filnamet som är valt
    persons.clear(); // Rensa nuvarande lista
    Person newPerson;
    while(getline(inFile, newPerson.firstName, DELIM)) { // person läser in info från filen
        getline(inFile, newPerson.lastName, DELIM);
        inFile >> newPerson.signature;
        inFile >> newPerson.height;
        inFile.get();
        persons.push_back(newPerson);
    }
    inFile.close(); // Stäng filen
}
void search_person(vector<Person> &persons) {
    string search_signature; // Vad användaren söker efter
    cout << "Search for a person by signature (yyyxxx): " << endl;
    cin >> search_signature;

    // Match komemr att peka på signaturen som matchar användarens input
    auto match = find_if(persons.begin(), persons.end(), [&search_signature](Person &p)
    {return p.signature == search_signature;});
    if (match == persons.end()) {
        cout << "No person found." << endl;
    }
    else {
        auto p = *match; // Det som match pekar på vilket är signaturen
        cout << left << setw(20) << "Sign" << setw(60) << "Name" << "Length [m]" << endl;
        cout << left << fixed << setprecision(2);
        cout << setw(20) << p.signature;
        cout << setw(40) << p.firstName + " " + p.lastName;
        cout << setw(30) << right << p.height << endl;
    }
}
void delete_person(vector<Person> &persons) {
    // Samma som search_person för att hitta personen
    string search_signature; // Vad användaren söker efter
    cout << "Search for a person by signature (yyyxxx): " << endl;
    cin >> search_signature;

    // Match komemr att peka på signaturen som matchar användarens input
    auto match = find_if(persons.begin(), persons.end(), [&search_signature](Person &p)
    {return p.signature == search_signature;});
    if (match == persons.end()) {
        cout << "No person found." << endl;
    }
    else {
        auto p = *match; // Det som match pekar på vilket är signaturen
        persons.erase(match);
        cout << "The person has been deleted!" << endl;
    }
}

