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

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void startLocalGame();

    void startEngineGame();

    void updatePlayer2ColorLabel() const;

    void proceedToGamePage();

    void drawBoardFromModel();

    void handlePromotionRequested(const Coordinates &coordinates, const ChessColor &color);


private:
    Ui::MainWindow *ui_;
    GameMode current_game_mode_;
    QGraphicsScene *scene_ = nullptr;
    ChessController *controller_ = nullptr;
    GameSettings game_settings_;


    void showConfigScreen(GameMode mode);

    void drawBoardTiles();

    void placePiece(const QString &svg_path, PieceColor color, int row, int col);
};

#endif // MAINWINDOW_H
