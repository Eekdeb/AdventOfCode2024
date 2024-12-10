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

vector<vector<int>> readMap(const string& filename) {
    vector<vector<int>> vectors;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
    }
    string line;
    while (getline(inputFile, line)) {
        vector<int> vec;
        istringstream iss(line);
        int num;

        while (iss >> num) {
            vec.push_back(num);
        }
        vectors.push_back(vec);
    }
    inputFile.close();
    return vectors;
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