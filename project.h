// Header-file för projektet

#ifndef DT018G_PROJECT_H
#define DT018G_PROJECT_H

#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <random>
using namespace std;

struct Person {
    string firstName;
    string lastName;
    string signature;
    double height;
};
enum Sort{lastName, signature, height, randomize};

const char DELIM = '|';

//Funktionsprotoyp
void menu();
void add_person(vector<Person> &persons); // Skriv in namn
bool check_signature(string &str); // Kolla yyyxxx, signaturen
bool yes_no(const string &str); // Används för ja/nej frågor
void print_list(vector<Person> &persons); // Visa listan
void sort_list(vector<Person> &persons, Sort method);
void perform_sort(vector<Person> &persons); // Skriv in hur den ska sorteras
bool compare_by_lastname(const Person &a, const Person &b); // Sortera efternamn utan hänsyn till versaler
void save_to_file(vector<Person> &persons); // Spara det man skrivit in till filen
string name_file(); // Namge filen
void read_from_file(vector<Person> &persons); // Öppna och läs från filen
void search_person(vector<Person> &persons); // Leta efter person i listan (om den är tom måste filen läsas)
void delete_person(vector<Person> &persons); // Ta bort en person från listan via signatur

#endif //DT018G_PROJECT_H
