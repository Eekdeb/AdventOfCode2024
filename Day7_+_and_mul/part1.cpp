#include <iostream>
#include <vector>
#include "../FileReader.cpp"
#include <numeric>
#include <cmath>

using namespace std;

long long addOrmull(vector<long long> numbers, long long mul){
    if (mul == 0) return accumulate(numbers.begin(),numbers.end(),0LL);
    long long result = numbers[0];
    for(int i = 1; i < numbers.size(); i++) {
        if(mul % 2 == 0){
            result += numbers[i];
        }else{
            result *= numbers[i];
        }
        mul /= 2;
        
    }
    return result;
}

bool checkCombo(long long target,vector<long long> sequence){
    long long result = 0;
    long long combinations = 1LL << (sequence.size()-1);
    for (long long index = 0; index < combinations; index++)
    {
        if(addOrmull(sequence,index) == target){
            return true;
        }
    }
    return false;
}

long long checkCombos(vector<vector<long long>> combos, vector<long long> targets){
    long long result = 0;
    for (long long i = 0; i < combos.size(); i++)
    {
        if(checkCombo(targets[i],combos[i])){
            result += targets[i];
        };
    }
  
    return result;
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
    long long check = checkCombos(input,targets);
    cout << check << endl;
    //1038838357795 correct
    return 0;
}