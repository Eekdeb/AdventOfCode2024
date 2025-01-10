#include <iostream>
#include <vector>
#include "../FileReader.cpp"
#include <numeric>
#include <cmath>
#include <set>

using namespace std;

long long calculateValue(int count, int start, int weight) {
    return static_cast<long long>(count) * (2 * start + count - 1) / 2 * weight;
}

int main() {
    string filename = "input.txt";
    string fileContent;
    vector<int> values, indexMapping;

    fileContent = getLine(filename);
    transform(fileContent.begin(), fileContent.end(), back_inserter(values), [](char c) { return c - '0'; });

    indexMapping = values;
    int currentIndex = 0;
    long long result = 0;
    int scalingFactor = (values.size() - 1) / 2;

    for (size_t i = values.size() - 1; i > 0; i -= 2) {
        bool foundSpace = false;
        int currentSize = values[i];
        
        for (size_t j = 1; j < i; j += 2) {
            if (currentSize <= values[j]) {
                currentIndex = accumulate(indexMapping.begin(), indexMapping.begin() + j, 0);
                currentIndex += indexMapping[j] - values[j];
                values[j] -= currentSize;
                result += calculateValue(currentSize, currentIndex, scalingFactor);
                foundSpace = true;
                break;
            }
        }

        if (!foundSpace) {
            currentIndex = accumulate(indexMapping.begin(), indexMapping.begin() + i, 0);
            result += calculateValue(currentSize, currentIndex, scalingFactor);
        }

        scalingFactor--;
    }

    cout << result << endl;
    return 0;
}
