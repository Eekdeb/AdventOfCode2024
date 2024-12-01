#include "../FileReader.cpp"
#include <algorithm>

int main() {
    string filename = "Input.txt";
    vector<int> column1, column2;
    int totalDistance = 0;

    extractColumnsFromFile(filename, column1, column2);
    sort(column1.begin(),column1.end());
    sort(column2.begin(),column2.end());
    for(int i = 0; i < column1.size(); i++) {
        totalDistance += abs(column1[i]-column2[i]);
    }
    cout << totalDistance << endl;

    return 0;
}