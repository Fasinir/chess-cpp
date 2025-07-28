#include "DraggablePiece.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

void DraggablePiece::moveToSquare(int row, int col) {
    QRectF bounds = boundingRect();
    qreal scaleFactor = scale();
    qreal offsetX = (tileSize - bounds.width() * scaleFactor) / 2;
    qreal offsetY = (tileSize - bounds.height() * scaleFactor) / 2;
    setPos(col * tileSize + offsetX, (7-row) * tileSize + offsetY);

    originalRow = row;
    originalCol = col;
}

void DraggablePiece::revertToOriginalPosition() {
    moveToSquare(originalRow, originalCol);
}


DraggablePiece::DraggablePiece(const QString &svgPath, PieceColor color, int startRow, int startCol, int tileSize)
    : QGraphicsSvgItem(svgPath), color(color), tileSize(tileSize),
      originalRow(startRow), originalCol(startCol) {
    setFlags(ItemIsMovable | ItemSendsScenePositionChanges);
    setZValue(1);

    // Initial positioning
    QRectF bounds = boundingRect();
    qreal scaleFactor = tileSize / bounds.width();
    setScale(scaleFactor);
    qreal offsetX = (tileSize - bounds.width() * scaleFactor) / 2;
    qreal offsetY = (tileSize - bounds.height() * scaleFactor) / 2;
    setPos(startCol * tileSize + offsetX, (7-startRow) * tileSize + offsetY);
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);
}

void DraggablePiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseMoveEvent(event);
}

void DraggablePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseReleaseEvent(event);
    QPointF currentScenePos = this->scenePos();
    int newCol = static_cast<int>(currentScenePos.x() + tileSize / 2) / tileSize;
    int newRow = 7 - static_cast<int>(currentScenePos.y() + tileSize / 2) / tileSize;

    newCol = std::clamp(newCol, 0, 7);
    newRow = std::clamp(newRow, 0, 7);

    // Emit intent to move — controller handles legality
    emit pieceMoved(originalRow, originalCol, newRow, newCol);

}
