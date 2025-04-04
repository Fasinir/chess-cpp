#include "Field.h"
#include <ostream>

std::ostream &operator<<(std::ostream &os, const Field &field) {
    if (field.hasFigure()) {
        os << *field.figure;
    } else {
        os << "_";
    }
    return os;
}

void Field::placeFigure(std::unique_ptr<Figure> figure) {
    this->figure = std::move(figure);
}

void Field::removeFigure() {
    this->figure.reset();
}

Field::Field(const Field &other) {
    if (other.figure) {
        figure = other.figure->clone();
    }
}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        if (other.figure) {
            figure = other.figure->clone();
        } else {
            figure.reset();
        }
    }
    return *this;
}

bool Field::hasFigure() const {
    return this->figure != nullptr;
}
