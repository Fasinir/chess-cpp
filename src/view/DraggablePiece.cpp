#include "DraggablePiece.h"
#include <QGraphicsScene>

DraggablePiece::DraggablePiece(const QString &svgPath, PieceColor color, int startRow, int startCol, int tileSize)
    : QGraphicsSvgItem(svgPath), color(color), tileSize(tileSize),
    originalRow(startRow), originalCol(startCol) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsScenePositionChanges);
    setZValue(1);

    // Position piece on board
    QRectF bounds = boundingRect();
    qreal scaleFactor = tileSize / bounds.width();
    setScale(scaleFactor);
    qreal offsetX = (tileSize - bounds.width() * scaleFactor) / 2;
    qreal offsetY = (tileSize - bounds.height() * scaleFactor) / 2;
    setPos(startCol * tileSize + offsetX, startRow * tileSize + offsetY);
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);
}

void DraggablePiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseMoveEvent(event);
}

void DraggablePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QPointF currentScenePos = this->scenePos();
    int newCol = static_cast<int>(currentScenePos.x() + tileSize / 2) / tileSize;
    int newRow = static_cast<int>(currentScenePos.y() + tileSize / 2) / tileSize;

    newCol = std::clamp(newCol, 0, 7);
    newRow = std::clamp(newRow, 0, 7);

    QPointF snappedPos(newCol * tileSize, newRow * tileSize);

    // Remove opponent piece if present
    QList<QGraphicsItem *> itemsAtPos = scene()->items(QRectF(snappedPos, QSizeF(tileSize, tileSize)));
    for (QGraphicsItem *item : itemsAtPos) {
        if (item == this) continue;

        auto *otherPiece = dynamic_cast<DraggablePiece *>(item);
        if (otherPiece && otherPiece->color != this->color) {
            scene()->removeItem(otherPiece);
            delete otherPiece;
            break;
        }
    }

    // Snap to square with centering
    QRectF bounds = boundingRect();
    qreal scaleFactor = scale();
    qreal offsetX = (tileSize - bounds.width() * scaleFactor) / 2;
    qreal offsetY = (tileSize - bounds.height() * scaleFactor) / 2;

    setPos(snappedPos.x() + offsetX, snappedPos.y() + offsetY);

    // Notify controller
    emit pieceMoved(originalRow, originalCol, newRow, newCol);

    // Update internal state
    originalRow = newRow;
    originalCol = newCol;

    QGraphicsSvgItem::mouseReleaseEvent(event);
}
