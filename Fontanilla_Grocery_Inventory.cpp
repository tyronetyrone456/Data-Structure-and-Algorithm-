#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

string vectorToString(const vector<string>& vec, const string& label) {
    string result = label + " [";
    for (size_t i = 0; i < vec.size(); ++i) {
        result += "\"" + vec [i] + "\"";
        if (i < vec.size() - 1) result += ", ";
    }
    result += "]\n";
    return result;
}

int main() {
    vector<string> Invent = {"apples", "bananas", "orange", "pears"};
    vector<string> ship = {"kiwis", "bananas", "grapes"};
    unordered_set<string> soldItems = {"apples", "oranges"};

    cout << vectorToString(Invent, "Current Inventory:");
    cout << vectorToString(ship, "Shipment:");

    unordered_set<string> updatedInventSet(Invent.begin(), Invent.end());

    for(const auto& item : ship) {
        updatedInventSet.insert (item);
    }

    for(const auto& item : soldItems) {
        updatedInventSet.erase (item);
    }

    vector<string> updatedInvent(updatedInventSet.begin(), updatedInventSet.end());

    cout << vectorToString(vector<string>(soldItems.begin(), soldItems.end()), "Sold-out items:");
    cout << vectorToString(updatedInvent, "Updated Inventory:");

    return 0;

}