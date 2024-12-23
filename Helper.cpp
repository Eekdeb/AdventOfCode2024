#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

template <typename T>
void printVec(std::vector<T> vector){
    for(auto value:vector){
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

std::vector<std::string> rotate90(std::vector<std::string> map) {
    size_t rows = map.size();
    size_t cols = map[0].length();
    std::vector<std::string> newMap(cols, std::string(rows, ' '));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            newMap[j][rows - i - 1] = map[i][j];
        }
    }
    return newMap;
}

std::vector<std::string> rotate45Right(std::vector<std::string> map) {
    size_t rows = map.size();
    size_t cols = map[0].length();

    size_t newRows = rows + cols - 1;
    std::vector<std::string> newMap(newRows);
    for (size_t i = 0; i < newRows; i++) {
        size_t length = std::min({i + 1, newRows - i, cols, rows});
        newMap[i] = std::string(length, ' ');
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            newMap[i + j] += map[i][j];
        }
    }
    return newMap;
}

std::vector<std::string> rotate45Left(const std::vector<std::string>& map) {
    size_t rows = map.size();
    size_t cols = map[0].length();
    size_t newRows = rows + cols - 1;

    std::vector<std::string> newMap(newRows);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (newMap[rows - 1 - i + j].empty()) {
                newMap[rows - 1 - i + j] = std::string(std::max(rows, cols), ' ');
            }
            newMap[rows - 1 - i + j][j] = map[i][j];
        }
    }

    for (auto& row : newMap) {
        row.erase(row.find_last_not_of(' ') + 1);
    }

    return newMap;
}

std::vector<int> extractIntegers(const std::string& input) {
    std::regex regex_numbers(R"(\d+)");
    std::sregex_iterator it(input.begin(), input.end(), regex_numbers);
    std::sregex_iterator end;

    std::vector<int> integers;

    while (it != end) {
        integers.push_back(std::stoi(it->str()));
        ++it;
    }

    return integers;
}

void print(int number){
    std::cout << number << std::endl;
}
void print(std::string str){
    std::cout << str << std::endl;
}