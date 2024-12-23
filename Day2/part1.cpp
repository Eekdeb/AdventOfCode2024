#include "../FileReader.cpp"
#include <algorithm>
#include <tuple>

void printVec(vector<int> v){
    for(auto s:v){
        cout << s << " ";
    }
    cout << endl;
}

tuple<bool,int> evaluateLine(const vector<int>& line){
    if(line[0] == line[1]){
        return {false,0};
    }
    bool positive  = line[0]-line[1] > 0;
    for(size_t i = 0; i < line.size()-1;i++){
        int diff = line[i] - line[i+1];
        if ((positive && (diff <= 0 || diff >= 4)) || 
            (!positive && (diff >= 0 || diff <= -4))) {
            return {false, static_cast<int>(i)};
        }
    }   
    return {true,0};
}

bool removeAndEvaluate(vector<int> line,const int index){
    line.erase(line.begin()+index);
    return get<0>(evaluateLine(line));
}

int countSafeCodes2(const vector<vector<int>>& map){
    //remove the first one
    int totalSecure = 0;

    for(const auto& line:map){
        bool safe;
        int failureIndex; 
        tie(safe,failureIndex) = evaluateLine(line);
        if(safe){
            totalSecure++;
        } else if (failureIndex >= 0 && (
            removeAndEvaluate(line, failureIndex) ||
            removeAndEvaluate(line, failureIndex + 1) ||
            removeAndEvaluate(line, 0))) {
            totalSecure++;
        }
    }
    return totalSecure;
}

int countSafeCodes(const vector<vector<int>>& map){
    int totalSecure = 0;
    for(const auto& line:map){
        if(get<0>(evaluateLine(line))){
            totalSecure++;
        }
    }
    return totalSecure;
}

int main() {
    string filename = "input.txt";
    vector<vector<int>> map;

    map = fileToIntGrid(filename);

    int safe = countSafeCodes(map);
    cout << "Part1: " << safe << endl;

    int totalSecure = countSafeCodes2(map);
    cout << "Part2: " << totalSecure << endl;
    return 0;
}