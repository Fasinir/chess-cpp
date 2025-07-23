#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <QObject>
#include <QString>

class ChessController : public QObject {
    Q_OBJECT

public:
    explicit ChessController(QObject *parent = nullptr);

    void onPieceMoved(int fromRow, int fromCol, int toRow, int toCol);

private:
    QString toSquare(int row, int col);
};

#endif // CHESSCONTROLLER_H
