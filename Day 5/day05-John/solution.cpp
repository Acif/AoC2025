#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <vector>
#define DEBUG 0

struct Range {
    long long low, high;

    Range(std::string line) {
        std::string tempLow = "";
        std::string tempHigh = "";
        bool temp = false;

        for (char c : line) {
            if (c != '-' && !temp) {
                tempLow += c;
            } else {
                temp = true;
            }
            if (c != '-' && temp) {
                tempHigh += c;
            }
        }

        this->low = std::stoll(tempLow);
        this->high = std::stoll(tempHigh);
    }
    Range(long long min, long long max) {
        this->low = min;
        this->high = max;
    }
    bool operator == (const Range &r) {
        if (low == r.low && high == r.high) {
            return true;
        }
        return false;
    } 
};

int concatenateRanges(std::vector<Range>&);

int main() {
    std::ifstream file("input.txt");
    std::string line;

    std::vector<Range> ranges;
    std::vector<long long> ids;

    bool rangesComplete = false;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.empty()) {
                rangesComplete = true;
                continue;
            }
            if (!rangesComplete) ranges.push_back(Range(line));
            if (rangesComplete) ids.push_back(std::stoll(line));
        }
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }

    #if DEBUG
    for (Range r : ranges) {
        std::cout << r.low << " " << r.high << std::endl;
    }

    for (long long l : ids) {
        std::cout << l << std::endl;
    }
    std::cout << std::endl;
    #endif

    auto start = std::chrono::high_resolution_clock::now();
    int freshIDs = 0;
    for (int i = 0; i < ids.size(); i++) {
        bool fresh = false;
        for (Range r : ranges) {
            if (ids[i] >= r.low && ids[i] <= r.high) {
                if (!fresh) {
                    freshIDs++;
                }
                fresh = true;
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    long long freshRanges = 0;
    while (concatenateRanges(ranges) != 0) continue;
    for (Range r : ranges) {
        #if DEBUG
        std::cout << r.low << " " << r.high << std::endl;
        #endif

        freshRanges += r.high - r.low + 1;
    }
    auto stop2 = std::chrono::high_resolution_clock::now();

    std::cout << "Fresh IDs: " << freshIDs << std::endl;
    std::cout << "Fresh Ranges:  " << freshRanges << std::endl << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    std::cout << "Part One Duration: " << duration.count() << " Microseconds" << std::endl
              << "Part Two Duration: " << duration2.count() << " Microseconds" << std::endl;

    return 0;
}

int concatenateRanges(std::vector<Range> &ranges) {
    int startingLength = ranges.size();
    std::vector<Range> newRanges;

    for (Range r1 : ranges) {
        bool found = false;
        for (Range r2 : ranges) {
            if (r1.low == r2.low && r1.high == r2.high) {
                continue;
            } else if (r1.low >= r2.low && r1.low <= r2.high ||
                       r1.high >= r2.low && r1.high <= r2.high) {

                long long low = (r1.low <= r2.low) ? r1.low : r2.low;
                long long high = (r1.high >= r2.high) ? r1.high : r2.high;

                newRanges.push_back(Range(low, high));
                found = true;
            }
        }
        if (!found) {
            newRanges.push_back(r1);
        }
    }

    for (int i = 0; i < newRanges.size(); i++) {
        for (int j = i + 1; j < newRanges.size();) {
            if (newRanges[j] == newRanges[i])
                newRanges.erase(newRanges.begin() + j);
            else
                j++;
        }
    }
    int newLength = newRanges.size();

    ranges.clear();
    std::copy(newRanges.begin(), newRanges.end(), std::back_inserter(ranges));

    return startingLength - newLength;
}