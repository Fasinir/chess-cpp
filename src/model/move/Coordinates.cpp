#include "Coordinates.h"

#include "../core/Constants.h"
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
    const int fileIndex = this->getX();
    const char file = Constants::kFiles.at(fileIndex);
    const int rankIndex = this->getY() + 1;
    return std::string(1, file) + std::to_string(rankIndex);
}

Coordinates Coordinates::fromAlgebraicNotation(const std::string &algebraicNotation) {
    char file = algebraicNotation.at(0);
    int yCoordinate = algebraicNotation.at(1) - '0' - 1;
    auto it = std::find(Constants::kFiles.begin(), Constants::kFiles.end(), file);
    int xCoordinate = std::distance(Constants::kFiles.begin(), it);
    return Coordinates(xCoordinate, yCoordinate);
}

bool Coordinates::operator==(const Coordinates &b) const {
    return this->getX() == b.getX() && this->getY() == b.getY();
}
