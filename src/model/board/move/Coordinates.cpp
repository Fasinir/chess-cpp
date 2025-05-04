#include "Coordinates.h"

#include "../../Constants.h"
#include <algorithm> // for std::find

std::ostream &operator<<(std::ostream &os, const Coordinates &coordinates) {
    os << "[" << coordinates.x << ", " << coordinates.y << "]";
    return os;
}

int Coordinates::getX() const {
    return x;
}

int Coordinates::getY() const {
    return y;
}

std::string Coordinates::toAlgebraicNotation() const {
    int fileIndex = this->getX();
    char file = Constants::FILES.at(fileIndex);
    int rankIndex = this->getY() + 1;
    return file + std::to_string(rankIndex);
}

Coordinates Coordinates::fromAlgebraicNotation(const std::string &algebraicNotation) {
    char file = algebraicNotation.at(0);
    int yCoordinate = algebraicNotation.at(1) - '0' - 1;
    auto it = std::find(Constants::FILES.begin(), Constants::FILES.end(), file);
    int xCoordinate = std::distance(Constants::FILES.begin(), it);
    return Coordinates(xCoordinate, yCoordinate);
}

bool Coordinates::operator==(const Coordinates &b) const {
    return this->getX() == b.getX() && this->getY() == b.getY();
}
