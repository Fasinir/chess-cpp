#ifndef DRAGGABLEPIECE_H
#define DRAGGABLEPIECE_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>

enum class PieceColor { White, Black };

class DraggablePiece : public QGraphicsSvgItem {
    Q_OBJECT

public:
    DraggablePiece(const QString &svgPath, PieceColor color, int startRow, int startCol, int tileSize);

    PieceColor color;

signals:
    void pieceMoved(int fromRow, int fromCol, int toRow, int toCol);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int tileSize;
    int originalRow;
    int originalCol;
};

#endif // DRAGGABLEPIECE_H
