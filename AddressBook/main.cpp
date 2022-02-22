#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Addressee {
    int id, userId;
    string name, surname, email, phoneNumber, address, password;
};
struct User {
    int userId;
    string userName, password;
};
string loadLine() {
    string line = "";
    getline(cin, line);
    return line;
}
string intToString(int liczba) {
    ostringstream ss;
    ss << liczba;
    string str = ss.str();
    return str;
}
int readTheLastId () {
    Addressee person;
    char separator = '|';
    int numberOfPeople = 0;
    string line;
    int lineNumber = 0;
    int id;

    fstream file;
    file.open("Adresaci.txt", ios::in);
    if (file.good() == false) {
        cout << "Plik z adresatami nie istnieje." << endl;
    }
    system ("pause");

    while(getline(file, line, separator)) {
        switch(lineNumber) {
        case 0:
            person.id = atoi(line.c_str());
            break;
        case 1:
            person.userId = atoi(line.c_str());
        case 2:
            person.name = line;
            break;
        case 3:
            person.surname = line;
            break;
        case 4:
            person.email = line;
            break;
        case 5:
            person.phoneNumber = line;
            break;
        case 6:
            person.address = line;
            break;
        }
        if (lineNumber >= 6) {
            numberOfPeople = person.id;
            lineNumber = 0;
        } else {
            lineNumber++;
        }
    }
    return numberOfPeople;
}
void addAddresseeToFile(Addressee person, int numberOfPeople, int userId) {
    fstream file;
    file.open("Adresaci.txt", ios::out | ios::app);
    if (file.good() == true) {
        file << person.id << '|';
        file << person.userId << '|';
        file << person.name << '|';
        file << person.surname << '|';
        file << person.email << '|';
        file << person.phoneNumber << '|';
        file << person.address << '|' << endl;
        person.id++;

        file.close();
        cout << endl;
        cout << "Adresat zostal dodany." << endl;
        system("pause");

    } else {
        cout << "Nie mozna otworzyc pliku: Ksiazka_adresowa.txt." << endl;
        system("pause");
    }
}
void addAddresseeToFileToAddressBook(vector<Addressee> &people, int numberOfPeople, int userId) {
    Addressee person;

    numberOfPeople = readTheLastId ();

    system("cls");
    if (numberOfPeople == 0) {
        person.id = 1;
    } else {
        person.id = numberOfPeople + 1;
    }

    person.userId = userId;

    cout << "Podaj imie: ";
    cin.sync();
    person.name = loadLine();

    cout << "Podaj nazwisko: ";
    person.surname = loadLine();

    cout << "Podaj email: ";
    person.email = loadLine();

    cout << "Podaj numer telefonu: ";
    person.phoneNumber = loadLine();

    cout << "Podaj adres: ";
    person.address = loadLine();

    people.push_back(person);

    addAddresseeToFile(person, numberOfPeople, userId);
}

Addressee downloadData(string line) {
    Addressee person;
    string singleData = "";
    int singleDataNumber = 1;

    for (int position = 0; position < line.length(); position++) {
        if (line[position] != '|') {
            singleData += line[position];
        } else {
            switch(singleDataNumber) {
            case 1:
                person.id = atoi(singleData.c_str());
                break;
            case 2:
                person.userId = atoi(singleData.c_str());
                break;
            case 3:
                person.name = singleData;
                break;
            case 4:
                person.surname = singleData;
                break;
            case 5:
                person.email = singleData;
                break;
            case 6:
                person.phoneNumber = singleData;
                break;
            case 7:
                person.address = singleData;
                break;
            }
            singleData = "";
            singleDataNumber++;
        }
    }
    return person;
}
void loadAddresseesFromFile(vector<Addressee> &people, int userId) {
    Addressee person;
    string dataOfOneAddressee = "";

    fstream file;
    file.open("Adresaci.txt", ios::in);

    if (file.good() == true) {
        while (getline(file, dataOfOneAddressee)) {
            person = downloadData(dataOfOneAddressee);
            if (person.userId == userId) {
                people.push_back(person);
            }
        }
        file.close();
    }
}
void searchByName(vector<Addressee> &people) {
    string namePerson;
    int numberOfAddressees = 0;

    system("cls");
    if(!people.empty()) {
        cout << "Podaj imie osoby ktora chcesz wyszukac: ";
        cin >> namePerson;

        for (vector <Addressee> ::iterator itr = people.begin(); itr != people.end(); itr++) {
            if (itr -> name == namePerson) {
                cout << endl;
                cout << itr -> id  << '|';
                cout << itr -> userId  << '|';
                cout << itr -> name << '|';
                cout << itr -> surname << '|';
                cout << itr -> email << '|';
                cout << itr -> phoneNumber << '|';
                cout << itr -> address << '|';
                numberOfAddressees++;
            }
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl;
    }
    system("pause");
}
void searchBySurname(vector<Addressee> &people) {
    string surnamePerson;
    int numberOfAddressees = 0;

    system("cls");
    if(!people.empty()) {
        cout << "Podaj nazwisko osoby, ktora chcesz wyszukac: ";
        cin >> surnamePerson;

        for (vector <Addressee> ::iterator itr = people.begin(); itr != people.end(); itr++) {
            if (itr -> surname == surnamePerson) {
                cout << endl;
                cout << itr -> id  << '|';
                cout << itr -> userId  << '|';
                cout << itr -> name << '|';
                cout << itr -> surname << '|';
                cout << itr -> email << '|';
                cout << itr -> phoneNumber << '|';
                cout << itr -> address << '|';
                numberOfAddressees++;
            }
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl;
    }
    system("pause");
}
void showAllPeopleInAddressBook(vector<Addressee> &people) {
    system("cls");
    if(!people.empty()) {
        for (vector <Addressee> ::iterator itr = people.begin(); itr != people.end(); itr++) {

            cout << endl;
            cout << itr -> id  << '|';
            cout << itr -> userId  << '|';
            cout << itr -> name << '|';
            cout << itr -> surname << '|';
            cout << itr -> email << '|';
            cout << itr -> phoneNumber << '|';
            cout << itr -> address << '|';
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl;
    }
    system("pause");
}
void updateAfterRemoved (vector<Addressee> &people, int idOfRemovedAddressee) {
    Addressee person;
    string dataOfOneAddressee = "";
    fstream file;
    file.open("Adresaci.txt", ios::in);
    fstream file2;
    file2.open("Adresaci_tymczasowi.txt", ios::out);

    if (file.good() == true) {
        while (getline(file, dataOfOneAddressee)) {
            person = downloadData(dataOfOneAddressee);
            if (person.id != idOfRemovedAddressee) {
                file2 << person.id << '|';
                file2 << person.userId << '|';
                file2 << person.name << '|';
                file2 << person.surname << '|';
                file2 << person.email << '|';
                file2 << person.phoneNumber << '|';
                file2 << person.address << '|' << endl;
            }
        }
        file2.close();
        file.close();
    }
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowi.txt", "Adresaci.txt");
}
void removeAddressee (vector<Addressee> &people) {
    int id,idOfRemovedAddressee;
    char key;

    system("cls");
    cout << "Podaj ID adresata, ktorego chcesz usunac: ";
    cin.sync();
    cin >> idOfRemovedAddressee;
    cin.sync();

    for (vector <Addressee> ::iterator itr = people.begin(); itr != people.end(); itr++) {
        if (itr->id == idOfRemovedAddressee) {
            cout << itr->id << '|';
            cout << itr -> userId << '|';
            cout << itr->name << '|';
            cout << itr->surname << '|';
            cout << itr->email << '|';
            cout << itr->phoneNumber << '|';
            cout << itr->address << endl;
            cout << "Potwierdz, ze chcesz usunac tego adresata wciskajac klawisz 't'" << endl;
            cin >> key;

            if (key == 't') {
                people.erase(itr);
                cout << "Adresat zostal usuniety";
                Sleep(1500);
                updateAfterRemoved(people, idOfRemovedAddressee);
            } else if (key != 't') {
                cout << "Adresat nie zostal usuniety";
                Sleep(1500);
            }
            break;
        }
    }
}
void updateAfterEdit(vector<Addressee> &people, int idEdit, int userId) {
    Addressee person;
    string dataOfOneAddressee = "";
    string lineWithData = "";

    fstream file;
    file.open("Adresaci.txt", ios::in);
    fstream file2;
    file2.open("Adresaci_tymczasowi.txt", ios::out);

    if (file.good() == true) {
        while (getline(file, dataOfOneAddressee)) {
            person = downloadData(dataOfOneAddressee);

            if (person.userId != userId) {
                file2 << person.id << '|';
                file2 << person.userId << '|';
                file2 << person.name << '|';
                file2 << person.surname << '|';
                file2 << person.email << '|';
                file2 << person.phoneNumber << '|';
                file2 << person.address << '|' << endl;
            } else {
                if (person.id == idEdit) {
                    for (vector <Addressee> ::iterator itr = people.begin(); itr != people.end(); itr++) {
                        lineWithData += intToString(itr->id) + '|';
                        lineWithData += intToString(itr->userId) + '|';
                        lineWithData += itr->name + '|';
                        lineWithData += itr->surname + '|';
                        lineWithData += itr->email + '|';
                        lineWithData += itr->phoneNumber + '|';
                        lineWithData += itr->address + '|';

                        file2 << lineWithData << endl;
                        lineWithData = "";
                    }
                }
            }
        }
        file2.close();
        file.close();
    }
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowi.txt", "Adresaci.txt");
}
void editAddressee (vector<Addressee> &people, int userId) {
    int idEdit, id;
    char number;

    system("cls");
    cout << "Podaj ID adresata, ktorego chcesz edytowac: ";
    cin.sync();
    cin >> idEdit;

    for (vector <Addressee> ::iterator itr = people.begin(); itr != people.end(); itr++) {
        if (itr-> id == idEdit) {
            cout << itr->id << '|';
            cout << itr->userId << '|';
            cout << itr->name << '|';
            cout << itr->surname << '|';
            cout << itr->email << '|';
            cout << itr->phoneNumber << '|';
            cout << itr->address << endl;
            cout << endl;

            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - email" << endl;
            cout << "4 - numer telefonu" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;
            cout << endl;
            cout << "Podaj numer danej, ktora chcesz edytowac: ";
            cin >> number;

            if (number == '1') {
                cout << "Podaj nowe imie: " << endl;
                string newName;
                cin >> newName;
                itr -> name = newName;
                updateAfterEdit(people, idEdit, userId);
            } else if (number == '2') {
                cout << "Podaj nowe nazwisko: " << endl;
                string newSurname;
                cin >> newSurname;
                itr -> surname = newSurname;
                updateAfterEdit(people, idEdit, userId);
            } else if (number == '3') {
                cout << "Podaj nowy email: " << endl;
                string newEmail;
                cin >> newEmail;
                itr -> email = newEmail;
                updateAfterEdit(people, idEdit, userId);
            } else if (number == '4') {
                cout << "Podaj nowy numer telefonu: " << endl;
                string newPhoneNumber;
                cin >> newPhoneNumber;
                itr -> phoneNumber = newPhoneNumber;
                updateAfterEdit(people, idEdit, userId);
            } else if (number == '5') {
                cout << "Podaj nowy adres: " << endl;
                string newAddress;
                cin >> newAddress;
                itr -> address = newAddress;
                updateAfterEdit(people, idEdit, userId);
            } else if (number == '6') {
            }
        }
    }
}
int registration (vector<User> &users, int numberOfUsers) {
    User user;
    string userName, password;
    int userId;
    int i = 0;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> userName;

    while (i < users.size()) {
        if (users[i].userName == userName) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> userName;
            i = 0;
        } else {
            i++;
            userId = users[users.size()-1].userId + 1;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;

    if (numberOfUsers == 0) {
        userId = 1;
    } else {
        userId = users[users.size()-1].userId + 1;
    }

    user.userId = userId;
    user.userName = userName;
    user.password = password;
    users.push_back(user);

    cout << "Konto zalozone" << endl;
    Sleep(1000);

    fstream file3;
    file3.open("Uzytkownicy.txt", ios::out | ios::app);
    if (file3.good()) {
        file3 << userId << '|';
        file3 << userName << '|';
        file3 << password << '|' << endl;

        file3.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: Ksiazka_adresowa.txt." << endl;
    }
    numberOfUsers++;
    return numberOfUsers;
}
int readUsersFromTextFile3(vector<User> &users) {
    User user;
    char separator = '|';
    int numberOfUsers = 0;
    string line;
    int lineNumber = 0;

    fstream file3;
    file3.open("Uzytkownicy.txt", ios::in);

    if (file3.good() == false) {
        cout << "Plik z uzytkownikami nie istnieje." << endl;
    }
    system ("pause");

    while(getline(file3, line, separator)) {
        switch(lineNumber) {
        case 0:
            user.userId = atoi(line.c_str());
            break;
        case 1:
            user.userName = line;
            break;
        case 2:
            user.password = line;
            break;
        }
        if (lineNumber >= 2) {
            users.push_back(user);
            lineNumber = 0;
            numberOfUsers++;
        } else {
            lineNumber++;
        }
    }
    file3.close();
    return numberOfUsers;
}
int login (vector<User> &users, vector<Addressee> &people) {
    string userName, password;
    int i = 0;
    int userId;

    cout << "Podaj nazwe: ";
    cin >> userName;

    while (i < users.size()) {
        if (users[i].userName == userName) {
            for (int attemps = 0; attemps < 3; attemps++) {
                cout << "Podaj haslo. Pozostalo prob: " << 3 - attemps << ": ";
                cin >> password;
                if (users[i].password == password) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    userId = users[i].userId;
                    return userId;
                }
            }
            cout << "Podales 3 razy bledne haslo." << endl;
            Sleep(1000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika o takim loginie." << endl;
    Sleep(1000);
    return 0;
}
void update (vector<User> &users) {
    fstream file4;
    file4.open("Uzytkownicy.txt", ios::out);

    if (file4.good() == true) {
        for (int i = 0; i < users.size(); i++) {
            file4 << users[i].userId << '|';
            file4 << users[i].userName << '|';
            file4 << users[i].password << '|' << endl;
        }
        file4.close();
    }
}
void passwordChange (vector<User> &users) {
    string userName, userNameEdit;
    cout << "Wprowadz nazwe uzytkownika, ktory chce zmienic haslo: ";
    cin >> userNameEdit;

    for (vector <User> ::iterator itr = users.begin(); itr != users.end(); itr++) {
        if (itr -> userName == userNameEdit) {
            cout << "Podaj nowe haslo: " << endl;
            string newPassword;
            cin >> newPassword;
            itr -> password = newPassword;
            cout << "Haslo zostalo zmienione";
            Sleep (1000);
        }
    }
    update(users);
}
int main() {
    int numberOfUsers = 0;
    int userId = 0;
    char choice;
    int numberOfPeople;
    vector<User> users;
    vector<Addressee> people;

    numberOfUsers = readUsersFromTextFile3(users);

    while(true) {
        system ("cls");
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "3. Zamknij program" << endl;

        cin>>choice;

        if (choice == '1') {
            numberOfUsers = registration (users, numberOfUsers);
        } else if (choice == '2') {
            userId = login(users, people);
            loadAddresseesFromFile(people, userId);
            while (userId >=1) {

                system ("cls");
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj uzytkownika" << endl;
                cout << "9. Zakoncz program" << endl;

                cin>>choice;
                switch(choice) {
                case '1':
                    addAddresseeToFileToAddressBook(people, numberOfPeople, userId);
                    break;
                case '2':
                    searchByName(people);
                    break;
                case '3':
                    searchBySurname(people);
                    break;
                case '4':
                    showAllPeopleInAddressBook(people);
                    break;
                case '5':
                    removeAddressee(people);
                    break;
                case '6':
                    editAddressee(people, userId);
                    break;
                case '7':
                    passwordChange(users);
                    break;
                case '8':
                    userId = 0;
                    people.clear();
                    break;
                case '9':
                    exit(0);
                    break;
                }
            }
        } else if (choice == '3') {
            exit(0);
        }
    }
    return 0;
}

