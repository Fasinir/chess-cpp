#include "DraggablePiece.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "../model/core/Constants.h"

void DraggablePiece::moveToSquare(int row, int col) {
    QRectF bounds = boundingRect();
    qreal scale_factor = scale();
    qreal offset_x = (tile_size_ - bounds.width() * scale_factor) / 2;
    qreal offset_y = (tile_size_ - bounds.height() * scale_factor) / 2;
    setPos(col * tile_size_ + offset_x, (Constants::kBoardSize - 1 - row) * tile_size_ + offset_y);

    original_row_ = row;
    original_col_ = col;
}

void DraggablePiece::revertToOriginalPosition() {
    moveToSquare(original_row_, original_col_);
}


DraggablePiece::DraggablePiece(const QString &svg_path, const ChessColor &color, int start_row, int start_col,
                               int tile_size)
    : QGraphicsSvgItem(svg_path), color_(color), tile_size_(tile_size),
      original_row_(start_row), original_col_(start_col) {
    setFlags(ItemIsMovable | ItemSendsScenePositionChanges);
    setZValue(1);

    // Initial positioning
    QRectF bounds = QGraphicsSvgItem::boundingRect();
    qreal scale_factor = tile_size / bounds.width();
    setScale(scale_factor);
    qreal offset_x = (tile_size - bounds.width() * scale_factor) / 2;
    qreal offset_y = (tile_size - bounds.height() * scale_factor) / 2;
    setPos(start_col * tile_size + offset_x, (Constants::kBoardSize - start_row) * tile_size + offset_y);
}

void DraggablePiece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);
}

void DraggablePiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseMoveEvent(event);
}

void DraggablePiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mouseReleaseEvent(event);
    QPointF current_scene_pos = this->scenePos();
    int new_col = static_cast<int>(current_scene_pos.x() + tile_size_ / 2) / tile_size_;
    int new_row = Constants::kBoardSize - 1 - static_cast<int>(current_scene_pos.y() + tile_size_ / 2) / tile_size_;

    new_col = std::clamp(new_col, 0, Constants::kBoardSize - 1);
    new_row = std::clamp(new_row, 0, Constants::kBoardSize - 1);

    // Emit intent to move — controller handles legality
    emit pieceMoved(original_row_, original_col_, new_row, new_col);
}
