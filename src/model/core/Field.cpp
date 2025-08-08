#include "Field.h"
#include <ostream>

std::ostream &operator<<(std::ostream &os, const Field &field) {
    if (field.hasFigure()) {
        os << *field.figure_.value();
    } else {
        os << "_";
    }
    return os;
}

Field::Field(const Field &other) {
    if (other.figure_) {
        figure_ = other.figure_.value()->clone();
    }
}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        if (other.figure_) {
            figure_ = other.figure_.value()->clone();
        } else {
            figure_.reset();
        }
    }
    return *this;
}

bool Field::hasFigure() const {
    return this->figure_.has_value();
}

void Field::removeFigure() {
    this->figure_.reset();
}

std::optional<std::shared_ptr<Figure> > Field::placeFigure(const std::shared_ptr<Figure>& figure) {
    std::optional<std::shared_ptr<Figure> > oldFigure = this->figure_;
    this->figure_ = figure;
    return oldFigure;
}

std::optional<std::shared_ptr<Figure> > Field::getFigure() const {
    return figure_;
}
