#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
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