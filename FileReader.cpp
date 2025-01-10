#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include "Helper.cpp"
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
    inputFile.close();
    return true;
}

vector<vector<int>> fileToIntGrid(const string& filename) {
    vector<vector<int>> vectors;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
    }
    string line;
    while (getline(inputFile, line)) { 
        vectors.push_back(extractIntegers(line));
    }
    inputFile.close();
    return vectors;
}

vector<vector<int>> convertToVectorVectorInt(const string& filename) {
    vector<vector<int>> result;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        vector<int> row;
        for (char ch : line) {
            if (isdigit(ch)) {
                row.push_back(ch - '0');
            }
        }
        result.push_back(row);
    }

    file.close();
    return result;
}

vector<string> getLines(const string& filename) {
    vector<string> vectors;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
    }

    string line;
    while (getline(inputFile, line)) {
        vectors.push_back(line);
    }
    inputFile.close();
    return vectors;
}

string getLine(const string& filename) {
    string line;
    ifstream inputFile(filename);
    getline(inputFile, line);
    inputFile.close();
    return line;
}

void ordering(const string& filename, map<int, vector<int>>& greaterToSmaller, vector<vector<int>>& allVariants) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        vector<int> numbers = extractIntegers(line);
        if (numbers.empty()) {
            break;
        }
        
        for (size_t i = 1; i < numbers.size(); i++) {
            greaterToSmaller[numbers[i]].push_back(numbers[0]);
        }
    }
    while (getline(inputFile, line)) {
        allVariants.push_back(extractIntegers(line));
    }

    inputFile.close();
}