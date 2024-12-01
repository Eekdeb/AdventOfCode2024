#include "../FileReader.cpp"
#include <algorithm>
#include <map>

int main() {
    string filename = "Input.txt";
    vector<int> column1, column2;
    map<int, int> counts;
    int similarity = 0;

    extractColumnsFromFile(filename, column1, column2);
    for (int num : column2) {
        counts[num]++;
    }
    for(int num : column1) {
        similarity += num * counts[num];
    }
    cout << similarity << endl;
    
    return 0;
}