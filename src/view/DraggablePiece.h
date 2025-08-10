#ifndef DRAGGABLEPIECE_H
#define DRAGGABLEPIECE_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>

#include "../model/core/ChessColor.h"

class DraggablePiece final : public QGraphicsSvgItem {
    Q_OBJECT

public:
    void moveToSquare(int row, int col); // Called from controller/view

    void revertToOriginalPosition(); // Called on illegal move

    DraggablePiece(const QString &svg_path, const ChessColor &color, int start_row, int start_col, int tile_size);

    ChessColor color_;

signals:
    void pieceMoved(int from_row, int from_col, int to_row, int to_col);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int tile_size_;
    int original_row_;
    int original_col_;
};

#endif // DRAGGABLEPIECE_H
