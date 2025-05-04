#include "Field.h"
#include <ostream>

std::ostream &operator<<(std::ostream &os, const Field &field) {
    if (field.hasFigure()) {
        os << *field.figure.value();
    } else {
        os << "_";
    }
    return os;
}

Field::Field(const Field &other) {
    if (other.figure) {
        figure = other.figure.value()->clone();
    }
}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        if (other.figure) {
            figure = other.figure.value()->clone();
        } else {
            figure.reset();
        }
    }
    return *this;
}

bool Field::hasFigure() const {
    return this->figure.has_value();
}

void Field::removeFigure() {
    this->figure.reset();
}

std::optional<std::shared_ptr<Figure> > Field::placeFigure(const std::shared_ptr<Figure>& figure) {
    std::optional<std::shared_ptr<Figure> > oldFigure = this->figure;
    this->figure = figure;
    return oldFigure;
}

std::optional<std::shared_ptr<Figure> > Field::getFigure() const {
    return figure;
}
