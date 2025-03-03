#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>  // For numeric_limits

using namespace std;

// Function to display the menu options.
void printMenu() {
    cout << "Menu Options:" << endl;
    cout << "1. Search for an item frequency" << endl;
    cout << "2. Print all items with frequencies" << endl;
    cout << "3. Print histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to validate and obtain the menu choice from the user.
int getValidatedChoice() {
    int choice;
    while (true) {
        if (cin >> choice) {
            // Check if the choice is within the valid range.
            if (choice >= 1 && choice <= 4) {
                return choice;
            } else {
                cout << "Invalid option. Please enter a number between 1 and 4: ";
            }
        } else {
            // If extraction fails (non-integer input), clear error and ignore the rest of the line.
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Function to write the frequency data to frequency.dat.
void writeFrequencyData(const map<string, int>& freqMap) {
    ofstream outFile("frequency.dat");
    if (!outFile) {
        cerr << "Error: Could not open frequency.dat for writing." << endl;
        return;
    }
    for (const auto& pair : freqMap) {
        outFile << pair.first << " " << pair.second << endl;
    }
    outFile.close();
}

int main() {
    // Open the input file.
    ifstream inFile("CS210_Project_Three_Input_File.txt");
    if (!inFile) {
        cerr << "Error: Could not open CS210_Project_Three_Input_File.txt" << endl;
        return 1;
    }

    // Use a map to keep track of each item and its frequency.
    map<string, int> freqMap;
    string word;

    // Read every word (item) from the file.
    while (inFile >> word) {
        freqMap[word]++;
    }
    inFile.close();

    // Back up the frequency data into frequency.dat.
    writeFrequencyData(freqMap);

    // Main menu loop.
    while (true) {
        printMenu();
        int choice = getValidatedChoice();
        cout << endl;

        if (choice == 1) {
            // Option 1: Search for a specific item.
            cout << "Enter the item to search for: ";
            string item;
            if (!(cin >> item)) {
                cout << "Invalid input for item. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (freqMap.find(item) != freqMap.end()) {
                cout << "The frequency of \"" << item << "\" is: " << freqMap[item] << endl;
            } else {
                cout << "Item \"" << item << "\" not found." << endl;
            }
        } else if (choice == 2) {
            // Option 2: Print all items with their frequency counts.
            cout << "Item Frequencies:" << endl;
            for (const auto& pair : freqMap) {
                cout << pair.first << " " << pair.second << endl;
            }
        } else if (choice == 3) {
            // Option 3: Print a histogram of items.
            cout << "Histogram:" << endl;
            for (const auto& pair : freqMap) {
                cout << pair.first << " ";
                for (int i = 0; i < pair.second; i++) {
                    cout << "*";
                }
                cout << endl;
            }
        } else if (choice == 4) {
            // Option 4: Exit the program.
            cout << "Exiting program." << endl;
            break;
        }

        cout << endl;  // Adds an extra line for readability.
    }

    return 0;
}
