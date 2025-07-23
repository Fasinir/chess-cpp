#include "ChessController.h"

#include <iostream>
#include <QDebug>

ChessController::ChessController(QObject *parent)
    : QObject(parent) {
}

void ChessController::onPieceMoved(int fromRow, int fromCol, int toRow, int toCol) {
    QString from = toSquare(fromRow, fromCol);
    QString to = toSquare(toRow, toCol);
    qDebug() << "Move:" << from << "->" << to;
    std::cout << "Move:" << fromRow << "," << fromCol << "->" << toRow << "," << toCol << std::endl;
}

QString ChessController::toSquare(int row, int col) {
    char c = 'a' + col;
    QChar file = c;
    int rank = 8 - row;
    return QString("%1%2").arg(file).arg(rank);
}
