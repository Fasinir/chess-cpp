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
    void updatePlayer2ColorLabel() const;

    void proceedToGamePage();

    void drawBoardFromModel();

    void handlePromotionRequested(const Coordinates &coordinates, const ChessColor &color);

private:
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_ = nullptr;
    ChessController *controller_ = nullptr;
    GameSettings game_settings_;

    static const QColor kHighlightColor;
    static const QColor kWhiteFieldColor;
    static const QColor kBlackFieldColor;
    static constexpr int kTileSize = 80;

    QVector<QGraphicsItem *> move_highlights_;

    void showLegalMoveHighlights(int from_row, int from_col);

    void clearLegalMoveHighlights();

    void showConfigScreen();

    void drawBoardTiles();

    void placePiece(const QString &svg_path, const ChessColor &color, int row, int col);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
