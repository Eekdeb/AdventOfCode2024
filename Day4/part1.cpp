#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <numeric>
#include "../FileReader.cpp"
#include "../Helper.cpp"

using namespace std;

int findPattern(const string& line, const regex& regex_pattern) {
    smatch match;
    string::const_iterator search_start(line.cbegin());
    int counter = 0;

    while (regex_search(search_start, line.cend(), match, regex_pattern)) {
        counter++;
        search_start = match.suffix().first;
    }
    return counter;
}

int findXmas(vector<string> input){
    regex regexXMAS(R"(XMAS)");
    regex regexSAMX(R"(SAMX)");
    int counter = 0;
    for (const auto& line : input) {
            counter += findPattern(line, regexXMAS);
            counter += findPattern(line, regexSAMX);
    }
    return counter;
}

int main() {
    string filename = "input.txt";
    vector<string> input, input90, input45R, input45L;

    input = getLines(filename);

    input90 = rotate90(input);
    input45R = rotate45Right(input);
    input45L = rotate45Left(input);

    int counter = 0;
    counter += findXmas(input);
    counter += findXmas(input90);
    counter += findXmas(input45R);
    counter += findXmas(input45L);


    cout << counter << endl;

    return 0;
}