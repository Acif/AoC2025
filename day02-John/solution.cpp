#include <cstdint>
#include <iostream>
#include <regex>
#include <vector>
#include <fstream>

struct Range {
    std::string low, high;

    Range(std::string input) {
        std::string temp;
        std::smatch m;

        regex_search(input, m, std::regex("\\d*"));
        for (auto x : m) {
            temp.append(x);
        }

        this->low = temp;
        temp = "";

        regex_search(input, m, std::regex("\\d*$"));
        for (auto x : m) {
            temp.append(x);
        }

        this->high = temp;
    }
};

void partOne(std::vector<Range>);
void partTwo(std::vector<Range>);

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<Range> rangeList;
    int vectorPosition = 0;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            rangeList.push_back(Range(line));
        }
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }

    partOne(rangeList);
    partTwo(rangeList);

    return 0;
}

void partOne(std::vector<Range> rangeList) {
    const std::regex pattern("^(.*)\\1$");

    uint64_t sum = 0;

    uint64_t lowTemp, highTemp;
    for (auto x : rangeList) {
        lowTemp = std::stoll(x.low);
        highTemp = std::stoll(x.high);

        // std::cout << lowTemp << " " << highTemp << std::endl;
        for (uint64_t i = lowTemp; i <= highTemp; i++) {
            if (std::regex_match(std::to_string(i), pattern)) {
                sum = sum + i;
                // std::cout << "HIT [" << lowTemp << "-" << highTemp << "] : " << i << std::endl;
            }
        }
        // std::cout << std::endl;
    }

    std::cout << "Part One Sum: " << sum << std::endl;
}

void partTwo(std::vector<Range> rangeList) {
    std::regex pattern("(\\d*)\\1+");

    uint64_t sum = 0;

    uint64_t lowTemp, highTemp;
    for (auto x : rangeList) {
        lowTemp = std::stoll(x.low);
        highTemp = std::stoll(x.high);

        // std::cout << lowTemp << " " << highTemp << std::endl;
        for (uint64_t i = lowTemp; i <= highTemp; i++) {
            if (std::regex_match(std::to_string(i), pattern)) {
                sum = sum + i;
                // std::cout << "HIT [" << lowTemp << "-" << highTemp << "] : " << i << std::endl;
            }
        }
        // std::cout << std::endl;
    }

    std::cout << "Part Two Sum: " << sum << std::endl;
}