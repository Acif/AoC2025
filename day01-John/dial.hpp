#ifndef DIAL_HPP_
#define DIAL_HPP_

class dial {
  private:
    int pos;
    int posThrough;
    int zeros;
    int zerosThrough;

  public:
    dial();
    void rotate(char, int);
    void rotateThrough(char, int);
    int getZeros();
    int getZerosThrough();
};

dial::dial() {
    this->pos = 50;
    this->zeros = 0;
    return;
}

void dial::rotate(char direction, int amount) {
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

void dial::rotateThrough(char direction, int amount) {
    switch (direction) {
        case 'L':
            for (int i = 0; i < amount; i++) {
                this->posThrough = (this->posThrough - 1) % 100;

                if (this->posThrough == 0) {
                    this->zerosThrough++;
                }
            }
            break;
        case 'R':
            for (int i = 0; i < amount; i++) {
                this->posThrough = (this->posThrough + 1) % 100;

                if (this->posThrough == 0) {
                    this->zerosThrough++;
                }
            }
            break;
        default:
            break;
    }

    return;
}

int dial::getZeros() {
    return this->zeros;
}

int dial::getZerosThrough() {
    return this->zerosThrough;
}

#endif
