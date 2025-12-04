#include <iostream>
#include <string>
#include <fstream>
#define DEBUG 0

int findLargestJolt(std::string);

int main() {
    int sum = 0;

    // Input each line into findLargestJolt and add output to sum
    std::ifstream file("input.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            sum += findLargestJolt(line);
        }

        file.close();
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}

int findLargestJolt(std::string input) {
    char firstDigit = '0', secondDigit = '0';
    int firstDigitPosition;
    bool firstPasses = false, secondPasses = false;

    // Find the first large digit in the string
    for (int i = 0; i < input.length(); i++) {
        if (input[i] > firstDigit) {
            firstDigit = input[i];
            firstDigitPosition = i;
        }
    }

    // Find the second large digit in the string, starting from after the position of the first largest digit 
    for (int i = firstDigitPosition + 1; i < input.length(); i++) {
        if (input[i] > secondDigit) {
            secondDigit = input[i];
        }
    }

    // If both digits are actually in the string, they pass this check, and are passed to forward
    if (input.find(firstDigit) != std::string::npos) firstPasses = true; 
    if (input.find(secondDigit) != std::string::npos) secondPasses = true;

    std::string forward = "";
    if (firstPasses && secondPasses) {
        forward += firstDigit;
        forward += secondDigit;
        #if DEBUG
        std::cout << forward << std::endl;
        #endif
    } else {
        forward = "0";
    }

    //-----------------------------------------------------------------------
    // The below is functionally the same as the above, except you are instead checking backwards

    char firstDigitReverse = '0', secondDigitReverse = '0';
    int firstDigitPositionReverse;
    bool firstReversePasses = false, secondReversePasses = false;

    for (int i = input.length() - 1; i >= 0; i--) {
        if (input[i] > firstDigitReverse) {
            firstDigitReverse = input[i];
            firstDigitPositionReverse = i;
        }
    }

    for (int i = firstDigitPositionReverse - 1; i >= 0; i--) {
        if (input[i] > secondDigitReverse) {
            secondDigitReverse = input[i];
        }
    }

    if (input.find(firstDigitReverse) != std::string::npos) firstReversePasses = true;
    if (input.find(secondDigitReverse) != std::string::npos) secondReversePasses = true;

    std::string reverse = "";
    if (firstReversePasses && secondReversePasses) {
        reverse += secondDigitReverse;
        reverse += firstDigitReverse;
        #if DEBUG
        std::cout << reverse << std::endl;
        #endif
    } else {
        reverse = "0";
    }

    //-----------------------------------------------------------------------
    // If the number generated from the first half of this function is larger than the second, return it, otherwise return the other number

    if (std::stoi(forward) > std::stoi(reverse)) {
        return std::stoi(forward);
    } else {
        return std::stoi(reverse);
    }
}