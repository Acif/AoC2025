#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int checkRolls(std::vector<std::vector<char>>&);
int total = 0;

int main() {
    std::ifstream file("input.txt");
    std::string line;

    std::vector<std::vector<char>> vec;
    std::vector<char> endcap;
    bool top = false;

    int sum = 0;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (top == false) {
                for (int i = 0; i < line.size() + 2; i++) {
                    endcap.push_back('_');
                }
                vec.push_back(endcap);
                top = true;
            }

            std::vector<char> temp;
            
            temp.push_back('_');
            for (char c : line) {
                temp.push_back(c);
            }
            temp.push_back('_');

            vec.push_back(temp);
        }

        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
    vec.push_back(endcap);

    while (checkRolls(vec) != 0) continue;

    std::cout << "Total: " << total << std::endl;

    return 0;
}

int checkRolls(std::vector<std::vector<char>> &vec) {
    std::vector<std::vector<char>> duplicate = vec;
    int sum = 0;

    for (int i = 1; i < vec.size()-1; i++) {
        for (int j = 1; j < vec[i].size()-1; j++) {
            if (vec[i][j] == '@') {
                int count = 0;
                if (vec[i-1][j-1] == '@') count++;
                if (vec[i-1][j] == '@') count++;
                if (vec[i-1][j+1] == '@') count++;

                if (vec[i][j-1] == '@') count++;
                if (vec[i][j+1] == '@') count++;

                if (vec[i+1][j-1] == '@') count++;
                if (vec[i+1][j] == '@') count++;
                if (vec[i+1][j+1] == '@') count++;

                if (count < 4) {
                    sum++;
                    duplicate[i][j] = '.';
                }
            }
        }
    }

    vec = duplicate;
    total += sum;
    return sum;
}