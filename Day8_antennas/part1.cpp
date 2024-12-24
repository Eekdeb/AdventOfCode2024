#include <iostream>
#include <vector>
#include "../FileReader.cpp"
#include <numeric>
#include <cmath>
#include <set>

using namespace std;

struct pos
{
    int row;
    int column;

    pos(int x=0, int y=0) 
        : row(x), column(y)
    {
    }
    pos& operator=(const pos& a)
    {
        row=a.row;
        column=a.column;
        return *this;
    }
    pos operator+(const pos& a) const
    {
        return pos(row+a.row, column+a.column);
    }
    pos operator-(const pos& a) const
    {
        return pos(row-a.row,column-a.column);
    }
    friend ostream& operator<<(ostream& os, const pos& coord) {
        os << "(" << coord.row << ", " << coord.column << ")";
        return os;
    }
    bool operator<(const pos& a) const {
        return tie(row, column) < tie(a.row, a.column);
    }
    bool operator==(const pos& a) const
    {
        return (row == a.row && column == a.column);
    }
};

map<char,vector<pos>> getAntennas(vector<string> input){
    map<char,vector<pos>> antennas;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[0].length(); j++)
        {
            if(input[i][j] != '.'){
                pos  c = {i,j};
                antennas[input[i][j]].push_back(c);
            }
        }
    }
    return antennas;
}

void addNodes(const vector<pos>& antenna, set<pos>& nodes, const vector<string>& input){
    for (size_t i = 0; i < antenna.size(); i++)
    {
        for (size_t j = 0; j < antenna.size(); j++)
        {
            if(i!=j){
                pos node = antenna[i]+antenna[i]-antenna[j];
                if(node.row >= 0 && node.row < input.size() && node.column >= 0 && node.column < input[0].length()){
                    nodes.insert(node);
                }
            }
        }
    }
}

void addNodesPart2(const vector<pos>& antenna, set<pos>& nodes, const vector<string>& input){
    for (size_t i = 0; i < antenna.size(); i++)
    {
        for (size_t j = 0; j < antenna.size(); j++)
        {
            if(i!=j){
                pos node = antenna[i]+antenna[i]-antenna[j];
                while(node.row >= 0 && node.row < input.size() && node.column >= 0 && node.column < input[0].length()){
                    nodes.insert(node);
                    node = node+antenna[i]-antenna[j];
                }
            }else{
                nodes.insert(antenna[i]);
            }
        }
    }
}

int main() {
    string filename = "input.txt";
    vector<string> input;
    map<char,vector<pos>> antennas;
    input = getLines(filename);
    
    antennas = getAntennas(input);
    
    set<pos> nodes;
    for(auto antenna: antennas){
        addNodesPart2(antenna.second,nodes,input);
    }
    cout << nodes.size();
    return 0;
}