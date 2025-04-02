#ifndef FIELD_H
#define FIELD_H
#include <memory>

#include "figures/Figure.h"

class Figure;

class Field {
    std::unique_ptr<Figure> figure;

public:
    Field() = default;
    ~Field() = default;

    Field(const Field &other);

    Field& operator=(const Field& other);

    [[nodiscard]] bool hasFigure() const;

    void removeFigure();

    void placeFigure(std::unique_ptr<Figure> figure);

    friend std::ostream &operator<<(std::ostream &os, const Field &field);

};


#endif //FIELD_H
