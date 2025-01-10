#include <iostream>
#include <vector>
#include "../FileReader.cpp"
#include <numeric>
#include <cmath>
#include <set>

using namespace std;

long long getSmalThings(int count, int start, int weight) {
    return static_cast<long long>(count) * (2 * start + count - 1) / 2 * weight;
}

int main() {
    string filename = "input.txt";
    string input;
    vector<int> numbers;
    input = getLine(filename);
    
    transform(input.begin(), input.end(), back_inserter(numbers),[](char c) { return c - '0'; });
    int index = 0;
    long long sum = 0;

    int bigValue = (numbers.size()-1)/2;
    int bigIndex = numbers.size()-1;
    int bigLoop = numbers[bigIndex];
    
    int smalValue = 0;

    for (size_t i = 0; smalValue < bigValue; i++)
    {
        if(i%2 == 0){
            sum += getSmalThings(numbers[i],index,smalValue);
            smalValue++;
        }
        else{            
            int max = numbers[i]+index;
            for (; index < max; index++)
            {
                if(bigLoop == 0){
                    bigValue--;
                    bigIndex -= 2;
                    bigLoop = numbers[bigIndex];
                }
                sum += index*bigValue;
                bigLoop--;
            }
        }
    }
    if(bigLoop != 0){
        sum += getSmalThings(bigLoop,index,bigValue);
    }
    
    cout << sum << endl;
    return 0;
}