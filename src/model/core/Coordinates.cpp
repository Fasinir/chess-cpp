#include "Coordinates.h"

#include "../../Constants.h"
#include <algorithm>

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
    os << "[" << coordinates.x_ << ", " << coordinates.y_ << "]";
    return os;
}

int Coordinates::getX() const {
    return x_;
}

int Coordinates::getY() const {
    return y_;
}

std::string Coordinates::toAlgebraicNotation() const {
    const int kFileIndex = this->getX();
    const char kFile = Constants::kFiles.at(kFileIndex);
    const int kRankIndex = this->getY() + 1;
    return std::string(1, kFile) + std::to_string(kRankIndex);
}

Coordinates Coordinates::fromAlgebraicNotation(const std::string &algebraic_notation) {
    char file = algebraic_notation.at(0);
    int y_coordinate = algebraic_notation.at(1) - '0' - 1;
    auto it = std::find(Constants::kFiles.begin(), Constants::kFiles.end(), file);
    int x_coordinate = std::distance(Constants::kFiles.begin(), it);
    return Coordinates(x_coordinate, y_coordinate);
}

bool Coordinates::operator==(const Coordinates &b) const {
    return this->getX() == b.getX() && this->getY() == b.getY();
}
