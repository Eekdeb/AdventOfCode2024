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

char nextChar(int &row, int& col,int rowOffset, int colOffset,const vector<string>& map, char search){    
    while (inRange(row+ rowOffset,col+ colOffset,map))
    {
        row += rowOffset;
        col += colOffset;
        if(map[row][col] == '#'){
            return map[row][col];
        }
        if(map[row][col] == search){
            return map[row][col];
        }
    }
    return map[row][col];
}

void checkBacktrack(int row, int col,const char direction,const vector<string>& map, int& count, int deep = 0){
    if(deep == 100){
        return;
    }  
    char t;
    switch (direction)
        {
        case 'U':
            t = nextChar(row,col,0,1,map,'R');
            if(t == 'R'){count++;}
            if(t == '#'){
                    checkBacktrack(row,col-1,'R',map,count,++deep);
                }
            break;
        case 'R':
            t = nextChar(row,col,1,0,map,'D');
            if(t == 'D'){count++;}
            if(t == '#'){
                    checkBacktrack(row-1,col,'D',map,count,++deep);
                }
            break;
        case 'D':
            t = nextChar(row,col,0,-1,map,'L');
            if(t == 'L'){count++;}
            if(t == '#'){
                    checkBacktrack(row,col+1,'L',map,count,++deep);
                }
            break;
        case 'L':
            t = nextChar(row,col,-1,0,map,'U');
            if(t == 'U'){count++;}
            if(t == '#'){
                    checkBacktrack(row+1,col,'U',map,count,++deep);
                }
            break;
        default:
            break;
    }
}


void move(int& row, int& col, int rowOffset, int colOffset,char direction, vector<string>& map, int& count) {
    while (inRange(row+rowOffset, col+colOffset, map) && 
           map[row + rowOffset][col + colOffset] != '#') 
    {
        row += rowOffset;
        col += colOffset;
        cout << row << " " << col << endl;
        checkBacktrack(row,col,direction,map,count);
        map[row][col] = direction;
    }
    if(!inRange(row+rowOffset, col+colOffset, map)){
        row += rowOffset;
        col += colOffset;
    }
}

int main() {
    string filename = "input.txt";
    vector<string> map;
    map = getLines(filename);
    cout << map.size() << " " << map[0].length() << endl;
    int row = -1, col = -1;
    for (int i = 0; i < map.size(); ++i) {
        size_t pos = map[i].find('^');
        if (pos != std::string::npos) {
            row = i;
            col = pos;
            break;
        }
    }
    int crossing = 0;
    while(true){
        move(row,col,-1,0,'U',map,crossing);
        if(!inRange(row,col,map)){
            print("U");
            break;
        }
        move(row,col,0,1,'R',map,crossing);
        if(!inRange(row,col,map)){
            print("R");
            break;
        }
        move(row,col,1,0,'D',map,crossing);
        if(!inRange(row,col,map)){
            print("D");
            break;
        }
        move(row,col,0,-1,'L',map,crossing);
        
        if(!inRange(row,col,map)){
            print("L");
            break;
        }
    }

    int count = 0;
    for(auto line:map){
        for(int i = 0; i < line.length()-1; i++){
            if(line[i] != '.' && line[i] != '#'){
                count++;
            }
        }
    }

    cout << count  << " " << crossing << endl;
    //1062 low
    //no 1461

    //504
    writeVectorToFile(map,"out.txt");
    
    return 0;
}