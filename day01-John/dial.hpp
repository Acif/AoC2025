#ifndef DIAL_HPP_
#define DIAL_HPP_

#include <iostream>

class Dial {
private:
    int pos;
    int posThrough;
    int zeros;
    int zerosThrough;

public:
    Dial() : pos(50), posThrough(50), zeros(0), zerosThrough(0) {}
    ~Dial() {
        std::cout << "Zeros: " << zeros << std::endl
                  << "Zeros Through: " << zerosThrough << std::endl;
    }

    void rotate(char direction, int amount) {
        switch (direction) {
            case 'L':
                pos = (pos - amount) % 100;
                break;
            case 'R':
                pos = (pos + amount) % 100;
                break;
        }
        if (pos == 0) {
            zeros++;
        }
    }

    void rotateThrough(char direction, int amount) {
        int direction_multiplier = (direction == 'L') ? -1 : 1;
        for (int i = 0; i < amount; i++) {
            posThrough = (posThrough + direction_multiplier) % 100;
            if (posThrough == 0) {
                zerosThrough++;
            }
        }
    }
};

#endif