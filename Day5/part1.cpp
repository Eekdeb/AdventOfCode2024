#include <iostream>
#include <string>
#include <vector>
#include "../FileReader.cpp"
#include <optional>

using namespace std;

optional<size_t> findAnyFromIndex(const vector<int>& sequence, const vector<int>& targets, size_t startIndex) {
    if (startIndex >= sequence.size()) {
        throw out_of_range("Start index is out of bounds.");
    }

    for (size_t i = startIndex; i < sequence.size(); ++i) {
        if (find(targets.begin(), targets.end(), sequence[i]) != targets.end()) {
            return i;
        }
    }
    return nullopt;
}

bool checkPageOrder(vector<int> pageNrs, map<int,vector<int>> greaterToSmaller){
    for (size_t i = 0; i < pageNrs.size(); i++)
    {
        if(findAnyFromIndex(pageNrs,greaterToSmaller[pageNrs[i]],i)){
            return false;
        }
    }
    return true;
}

bool correctPageOrder(vector<int>& pageNrs, map<int,vector<int>> greaterToSmaller){
    bool success = false;
        while(!success){
            success = true;
            for (size_t i = 0; i < pageNrs.size(); i++)
            {
                auto correctIndex = findAnyFromIndex(pageNrs,greaterToSmaller[pageNrs[i]],i);
                if(correctIndex){
                    swap(pageNrs[i], pageNrs[*correctIndex]);
                    success = false;
                    break;
                }
            }
        }
        cout << "Correct numbering: ";
        printVec(pageNrs);
    return success;
}


int main() {
    string filename = "input.txt";
    map<int,vector<int>> greaterToSmaller, smallerToGreater;
    vector<vector<int>> allPageNrs;
    vector<vector<int>> failedPageNrs;
    ordering(filename,greaterToSmaller,allPageNrs);
    
    int total = 0,total2 = 0;
    for(auto pageNrs:allPageNrs){
        printVec(pageNrs);
        if(checkPageOrder(pageNrs,greaterToSmaller)){
            total += pageNrs[(pageNrs.size()-1)/2];
        }
        else{
            correctPageOrder(pageNrs,greaterToSmaller);
            total2 += pageNrs[(pageNrs.size()-1)/2];
        }
    }

    cout << total << " " << total2 << endl;
    return 0;
}