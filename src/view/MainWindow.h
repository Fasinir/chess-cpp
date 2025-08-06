#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "DraggablePiece.h"
#include "../controller/ChessController.h"
#include "GameSettings.h"


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void startLocalGame();

    void startEngineGame();

    void updatePlayer2ColorLabel();

    void proceedToGamePage();

    void drawBoardFromModel();

    void handlePromotionRequested(Coordinates coordinates, ChessColor color);


private:
    Ui::MainWindow *ui;
    GameMode currentGameMode;
    QGraphicsScene *scene = nullptr;
    ChessController *controller = nullptr;
    GameSettings gameSettings;


    void showConfigScreen(GameMode mode);

    void drawChessBoard();

    void placePiece(const QString &svgPath, PieceColor color, int row, int col);
};

#endif // MAINWINDOW_H
