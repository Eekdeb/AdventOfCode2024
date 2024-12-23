#include <iostream>
#include <string>
#include <vector>
#include "../FileReader.cpp"

using namespace std;

void print(string p){
    cout << p << endl;
}

bool inRange(int row, int col, const vector<string>& map){
    return (row >= 0 && row < map.size()) && (col >= 0 &&  col < map[0].length()-1);
}

int traverseMap(vector<string> map, int startRow, int startCol, char firstMove,bool traversing = false, int putRow = 0,int putCol = 0) {
    int count = 0, supercount = 0;
    vector<pair<char, pair<int, int>>> moveOrder = {
        {'U', {-1, 0}},
        {'R', {0, 1}},
        {'D', {1, 0}},
        {'L', {0, -1}}
    };
    
    int row = startRow, col = startCol;
    size_t moveIndex = 0;

    for (size_t i = 0; i < moveOrder.size(); ++i) {
        if (moveOrder[i].first == firstMove) {
            moveIndex = i;
            break;
        }
    }

    if(traversing){
        map[putRow][putCol] = '#';
        //cout << putRow << " " << putCol << endl;
    }
    int max = map.size()*map[0].length() + 100;
    while (inRange(row, col, map) && count < max) {
        while (inRange(row, col, map) && count < max) {

            if(!traversing && inRange(row,col,map)){
                int trev = traverseMap(map,startRow,startCol,'U',true,row,col);
                if(trev >= max){
                    supercount++;

                    map[row][col] = '0';
                }
            }

            row += moveOrder[moveIndex].second.first;
            col += moveOrder[moveIndex].second.second;
            if(!inRange(row,col,map)){
                break;
            }
            if(map[row][col] == '#'){
                row -= moveOrder[moveIndex].second.first;
                col -= moveOrder[moveIndex].second.second;
                break;
            }

            count++;

        }
        if (!inRange(row, col, map)) {
            break;
        }
        moveIndex = (moveIndex + 1) % moveOrder.size();
    }
    if(!traversing){
        cout << "Final position: (" << row << ", " << col << ")" << count << " " << supercount << endl;
        writeVectorToFile(map, "out.txt");
    }
    return count;
}

int main() {
    string filename = "input.txt";
    vector<string> map;
    map = getLines(filename);
    int row = -1, col = -1;
    for (int i = 0; i < map.size(); ++i) {
        size_t pos = map[i].find('^');
        if (pos != std::string::npos) {
            row = i;
            col = pos;
            break;
        }
    }
    
    char firstMove = 'U';
    cout << row << " " << col << endl;
    int steps = traverseMap(map,row,col,firstMove);
    int count = 0;
    for(auto line:map){
        for(int i = 0; i < line.length()-1; i++){
            if(line[i] != '.' && line[i] != '#'){
                count++;
            }
        }
    }
    return 0;
}