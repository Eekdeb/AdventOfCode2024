#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool extractColumnsFromFile(const string& filename, vector<int>& column1, vector<int>& column2) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    int num1, num2;
    while (inputFile >> num1 >> num2) {
        column1.push_back(num1);
        column2.push_back(num2);
    }

    inputFile.close(); // Close the file
    return true; // Indicate success
}
