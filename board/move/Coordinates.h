#ifndef COORDINATES_H
#define COORDINATES_H
#include <ostream>


class Coordinates {
    int x;
    int y;

public:
    Coordinates(const int x, const int y) : x(x), y(y) {
    };

    ~Coordinates() = default;

    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);
};


#endif //COORDINATES_H
