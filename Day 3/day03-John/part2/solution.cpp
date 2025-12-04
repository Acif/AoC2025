#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    long long sum = 0;
    std::ifstream file("input.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string numbers = "";
        std::vector<char> original(line.begin(), line.end());
        int count = 12;

        while (numbers.size() != 12) {
            int max = 0;
            int index = 0;

            if (original.size() < count - numbers.size()) {
                for (int i = 0; i < count - numbers.size(); i++) {
                    numbers = numbers + original[original.size() - 1 - i];
                }
            } else {
                for (int i = 0; i < original.size() - (count - 1 - numbers.size()); i++) {
                    if (max < (original[i] - '0')) {
                        max = original[i] - '0';
                        index = i;
                    }
                }
                original.erase(original.begin(), original.begin() + index + 1);
            }

            numbers = numbers + std::to_string(max);
        }

        sum += std::stoll(numbers);
    }

    file.close();
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
