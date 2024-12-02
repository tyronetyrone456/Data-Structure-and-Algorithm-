#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Chore { string name, description; };
vector<Chore> chores;

void addChore() {
    Chore c;
    cout << "Name: "; cin.ignore(); getline(cin, c.name);
    cout << "Description: "; getline(cin, c.description);
    chores.push_back(c);
}

void displayChores() {
    for (int i = 0; i < chores.size(); ++i)
        cout << i + 1 << ". " << chores[i].name << " - " << chores[i].description << "\n";
}

void updateChore() {
    int n; displayChores();
    cout << "Update chore #: "; cin >> n; cin.ignore();
    if (n >= 1 && n <= chores.size()) addChore();
}

void deleteChore() {
    int n; displayChores();
    cout << "Delete chore #: "; cin >> n;
    if (n >= 1 && n <= chores.size()) chores.erase(chores.begin() + n - 1);
}

int main() {
    int choice;
    do {
        cout << "1. Add\n2. View\n3. Update\n4. Delete\n5. Exit\nChoice: "; cin >> choice;
        if (choice == 1) addChore();
        else if (choice == 2) displayChores();
        else if (choice == 3) updateChore();
        else if (choice == 4) deleteChore();
    } while (choice != 5);
    return 0;
}
