#include "../FileReader.cpp"
#include <algorithm>
#include <regex>

int extractMulInstances(const string& input) {
    regex regex_pattern(R"(mul\((\d+),(\d+)\))");
    smatch match;
    string::const_iterator search_start(input.cbegin());
    vector<string> results;
    int products = 0;

    while (regex_search(search_start, input.cend(), match, regex_pattern)) {
        int num1 = std::stoi(match[1].str());
        int num2 = std::stoi(match[2].str());
        products += num1*num2;
        search_start = match.suffix().first;
    }

    return products;
}

string removeAfterDont(const string& input) {
    string result = input;
    regex regex_dont(R"(don't\(\))");
    regex regex_do(R"(do\(\))");
    vector<pair<size_t, size_t>> ranges_to_erase;
    
    auto search_start = result.cbegin();
    smatch match_dont;
    while (regex_search(search_start, result.cend(), match_dont, regex_dont)) {
        auto dont_start = match_dont.position() + distance(result.cbegin(), search_start);
        auto dont_end = dont_start + match_dont.length();

        auto do_start_search = result.cbegin() + dont_end;
        smatch match_do;
        size_t erase_end = result.size();
        if (regex_search(do_start_search, result.cend(), match_do, regex_do)) {
            erase_end = match_do.position() + distance(result.cbegin(), do_start_search) + match_do.length();
            search_start = result.cbegin() + erase_end;
        } else {
            search_start = result.cbegin() + dont_end;
        }
        
        ranges_to_erase.emplace_back(dont_start, erase_end);
    }

    for (auto it = ranges_to_erase.rbegin(); it != ranges_to_erase.rend(); ++it) {
        result.erase(it->first, it->second - it->first);
    }
    return result;
}


int main() {
    string filename = "input.txt";
    vector<string> input;
    input = getLines(filename);

    //part 1
    int sum = 0;
    for (auto& line : input)
    {
        sum += extractMulInstances(line);
    }
    cout << sum << endl;

    //Part 2
    string one ="";
    for (auto& line : input)
    {
        one += line;
    }
    sum = extractMulInstances(removeAfterDont(one));
    cout << sum << endl;
    return 0;
}