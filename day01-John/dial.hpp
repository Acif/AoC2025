#ifndef DIAL_HPP_
#define DIAL_HPP_

#include <iostream>

class dial {
  private:
    int pos;
    int posThrough;

  public:
    int zeros;
    int zerosThrough;

    dial();
    ~dial();
    void rotate(char, int);
    void rotateThrough(char, int);
};

inline dial::dial() {
    this->pos = 50;
    this->zeros = 0;
    this->posThrough = 50;
    this->zerosThrough = 0;
    return;
}

inline dial::~dial() {
    std::cout << "Zeros: " << this->zeros << std::endl
              << "Zeros Through: " << this->zerosThrough << std::endl;
}

inline void dial::rotate(char direction, int amount) {
    switch (direction) {
        case 'L':
            this->pos = (this->pos - amount) % 100;
            break;
        case 'R':
            this->pos = (this->pos + amount) % 100;
            break;
        default:
            break;
    }

    if (this->pos == 0) {
        this->zeros++;
    }

    return;
}

enum Direction {
    LEFT = -1, RIGHT = 1
};

inline void dial::rotateThrough(char direction, int amount) {
    Direction d;
    
    switch (direction) {
        case 'L':
            d = LEFT;
            break;
        case 'R':
            d = RIGHT;
            break;
        default:
            break;
    }

    for (int i = 0; i < amount; i++) {
        this->posThrough = (this->posThrough + d) % 100;

        if (this->posThrough == 0) this->zerosThrough++;
    }

    return;
}

inline void test() {
    std::cout << "test" << std::endl;
}

#endif
