#include <cstdint>
#include <iostream>
#include <regex>
#include <vector>
#include <fstream>

#define DEBUG 0

/* 
INPUT FILE MUST NOT BE CSV, VALUES MUST BE ON NEW LINE:
123-456
789-101112
*/

struct Range {
    std::string low, high;

    Range(std::string input) {
        std::string temp;
        std::smatch m;

        // match the first number in a line, and define low as it
        regex_search(input, m, std::regex("\\d*"));
        for (auto x : m) {
            temp.append(x);
        }

        this->low = temp;
        temp = "";

        // match the second number in a line, and define high as it
        regex_search(input, m, std::regex("\\d*$"));
        for (auto x : m) {
            temp.append(x);
        }

        this->high = temp;
    }
};

void solve(std::vector<Range>, int);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<Range> rangeList; // vector containing range object for each line of input
    int vectorPosition = 0;

    // Append each line of input to rangeList with properly seperated values
    if (file.is_open()) {
        while (std::getline(file, line)) {
            rangeList.push_back(Range(line));
        }
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }

    solve(rangeList, 1);
    solve(rangeList, 2);

    return 0;
}

void solve(std::vector<Range> rangeList, int part) {
    std::regex pattern;
    if (part == 1) {
        pattern = "^(.*)\\1$"; // Matches if first and second half of string are the same
    } else if (part == 2) {
        pattern = "(\\d*)\\1+"; // Matches if any sequence of numbers repeats in an entire string 
    }

    uint64_t sum = 0;
    uint64_t lowTemp, highTemp;
    
    for (auto x : rangeList) {
        // Cast x.low and x.high to uint64_t (long long)
        lowTemp = std::stoll(x.low);
        highTemp = std::stoll(x.high);

        #if DEBUG
        std::cout << lowTemp << " " << highTemp << std::endl;
        #endif 
        // For each number between low and high of a range object, check if it matches the specified pattern
        for (uint64_t i = lowTemp; i <= highTemp; i++) {
            if (std::regex_match(std::to_string(i), pattern)) {
                sum = sum + i;
                #if DEBUG
                std::cout << "HIT [" << lowTemp << "-" << highTemp << "] : " << i << std::endl;
                #endif
            }
        }
        #if DEBUG
        std::cout << std::endl;
        #endif
    }

    std::cout << "Part " << part << " Sum: " << sum << std::endl;
}