#ifndef FIELD_H
#define FIELD_H
#include <memory>
#include <optional>

#include "../figures/Figure.h"


class Field {
    std::optional<std::shared_ptr<Figure> > figure;

public:
    Field() = default;

    ~Field() = default;

    Field(const Field &other);

    Field &operator=(const Field &other);

    [[nodiscard]] bool hasFigure() const;

    void removeFigure();

    std::optional<std::shared_ptr<Figure> > placeFigure(const std::shared_ptr<Figure>& figure);

    [[nodiscard]] std::optional<std::shared_ptr<Figure> > getFigure() const;

    friend std::ostream &operator<<(std::ostream &os, const Field &field);
};


#endif //FIELD_H
