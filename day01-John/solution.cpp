#include <iostream>
#include <fstream>
#include <string>
#include "dial.hpp"

int main() {
    dial dial;
    
    std::ifstream file("input.txt");
    std::string line;

    if (file.is_open()) {
        char rotationDirection;
        int rotationAmount;

        while (std::getline(file, line)) {
            rotationDirection = line.at(0);
            rotationAmount = std::stoi(line.substr(1, line.size()));

            dial.rotate(rotationDirection, rotationAmount);
            dial.rotateThrough(rotationDirection, rotationAmount);
        }

        file.close();
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }

    return 0;
}
