#ifndef FIELD_H
#define FIELD_H
#include <memory>

#include "Figure.h"


class Field {
    std::unique_ptr<Figure> figure;

public:
    Field() = default;

    bool hasFigure() const;

    void removeFigure();

    void placeFigure(std::unique_ptr<Figure> figure);

    friend std::ostream &operator<<(std::ostream &os, const Field &field);

    ~Field() = default;
};


#endif //FIELD_H
