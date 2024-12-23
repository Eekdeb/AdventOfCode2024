#include <iostream>
#include <vector>
#include "../FileReader.cpp"
#include <numeric>
#include <cmath>

using namespace std;

bool is_valid(long long target, vector<long long> numbers) {
    if (numbers.size() == 1) {
        return numbers[0] == target;
    }

    vector<long long> sumCombination = {numbers[0] + numbers[1]};
    sumCombination.insert(sumCombination.end(), numbers.begin() + 2, numbers.end());
    if (is_valid(target, sumCombination)) {
        return true;
    }
    vector<long long> productCombination = {numbers[0] * numbers[1]};
    productCombination.insert(productCombination.end(), numbers.begin() + 2, numbers.end());
    if (is_valid(target, productCombination)) {
        return true;
    }
    
    long long concatenated = stoll(to_string(numbers[0]) + to_string(numbers[1]));
    vector<long long> concatCombination = {concatenated};
    concatCombination.insert(concatCombination.end(), numbers.begin() + 2, numbers.end());
    if (is_valid(target, concatCombination)) {
        return true;
    
    }
    return false;
}

vector<vector<long long>> getFile(const string& filename, vector<long long>& target) {
    vector<vector<long long>> result;
    
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return result;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string keyPart, valuePart;
        if (getline(iss, keyPart, ':') && getline(iss, valuePart)) {
            long long key = stoll(keyPart);
            target.push_back(key);
            istringstream valueStream(valuePart);
            vector<long long> values;
            long long num;
            while (valueStream >> num) {
                values.push_back(num);
            }
            result.push_back(values);
        }
    }
    inputFile.close();
    return result;
}

int main() {
    string filename = "input.txt";
    vector<vector<long long>> input;
    vector<long long> targets;
    input = getFile(filename,targets);
    long long total = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if(is_valid(targets[i],input[i])){
            total += targets[i];
        }
    }
    
    cout << total << endl;
    //254136560217241 correct
    return 0;
}