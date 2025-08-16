#ifndef COORDINATES_H
#define COORDINATES_H
#include <ostream>
#include <functional>

class Coordinates {
    int x_;
    int y_;

public:
    Coordinates(const int kX, const int kY) : x_(kX), y_(kY) {
    }

    Coordinates(const Coordinates &other) = default;

    ~Coordinates() = default;

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    friend std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates);

    bool operator==(const Coordinates &b) const;

    [[nodiscard]] std::string toAlgebraicNotation() const;

    static Coordinates fromAlgebraicNotation(const std::string &algebraic_notation);
};

template<>
struct std::hash<Coordinates> {
    std::size_t operator()(const Coordinates &coord) const noexcept {
        return std::hash<int>()(coord.getX()) ^ std::hash<int>()(coord.getY()) << 1;
    }
};


#endif //COORDINATES_H
