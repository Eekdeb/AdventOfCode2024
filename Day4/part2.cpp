#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <numeric>
#include "../FileReader.cpp"
#include "../Helper.cpp"

using namespace std;

int findX_MAS(vector<string> map){
    int counter = 0;
    for (size_t row = 1; row < map.size()-1; row++)
    {
        for (size_t column = 1; column < map[0].length()-1; column++)
        {
            if(map[row][column] == 'A'){
                string corners = "";
                corners += map[row-1][column-1];
                corners += map[row-1][column+1];
                corners += map[row+1][column+1];
                corners += map[row+1][column-1];
                //"SMSM" "MSMS" is left and not correct
                if(corners == "SSMM" || corners == "MMSS" || corners == "SMMS" || corners == "MSSM"){
                    counter++;
                }
            }
        }
    }
    return counter;
}

int main() {
    string filename = "input.txt";
    vector<string> input;

    input = getLines(filename);
    int counter = findX_MAS(input);
    cout << counter << endl;
    return 0;
}