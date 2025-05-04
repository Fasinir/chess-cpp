#ifndef COORDINATES_H
#define COORDINATES_H
#include <ostream>


class Coordinates {
    int x;
    int y;

public:
    Coordinates(const int x, const int y) : x(x), y(y) {
    };

    Coordinates(const Coordinates &other) = default;

    ~Coordinates() = default;

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    friend std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);

    bool operator==(const Coordinates &b) const;

    [[nodiscard]] std::string toAlgebraicNotation() const;

    static Coordinates fromAlgebraicNotation(const std::string &algebraicNotation);
};


#endif //COORDINATES_H
