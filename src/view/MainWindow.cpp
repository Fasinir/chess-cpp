#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QGraphicsRectItem>
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    controller = new ChessController(this);

    connect(ui->startLocalGameButton, &QPushButton::clicked, this, &MainWindow::startLocalGame);
    connect(ui->startEngineGameButton, &QPushButton::clicked, this, &MainWindow::startEngineGame);
    connect(ui->colorComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updatePlayer2ColorLabel);
    connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::proceedToGamePage);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startLocalGame() {
    showConfigScreen(GameMode::Local);
}

void MainWindow::startEngineGame() {
    showConfigScreen(GameMode::Engine);
}

void MainWindow::showConfigScreen(GameMode mode) {
    currentGameMode = mode;
    ui->stackedWidget->setCurrentWidget(ui->configPage);

    bool isEngineGame = (mode == GameMode::Engine);
    ui->chessEngineComboBox->setVisible(isEngineGame);
    ui->playerTwoLineEdit->setVisible(!isEngineGame);
    ui->playerTwoColorLabel->setVisible(!isEngineGame);
}

void MainWindow::updatePlayer2ColorLabel() {
    const QString choice = ui->colorComboBox->currentText();

    if (choice == "White") {
        ui->playerTwoColorLabel->setText("Black");
    } else if (choice == "Black") {
        ui->playerTwoColorLabel->setText("White");
    } else {
        ui->playerTwoColorLabel->setText("Random color");
    }
}

void MainWindow::proceedToGamePage() {
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    drawChessBoard();

    // Place full set of pieces for both sides
    for (int col = 0; col < 8; ++col) {
        placePiece("../assets/black_pawn.svg", PieceColor::Black, 1, col);
        placePiece("../assets/white_pawn.svg", PieceColor::White, 6, col);
    }

    QStringList pieceOrder = {
        "rook", "knight", "bishop", "queen",
        "king", "bishop", "knight", "rook"
    };

    for (int col = 0; col < 8; ++col) {
        placePiece(QString("../assets/black_%1.svg").arg(pieceOrder[col]), PieceColor::Black, 0, col);
        placePiece(QString("../assets/white_%1.svg").arg(pieceOrder[col]), PieceColor::White, 7, col);
    }
}

void MainWindow::drawChessBoard() {
    if (scene) delete scene;
    scene = new QGraphicsScene(this);
    ui->boardGraphicsView->setScene(scene);
    ui->boardGraphicsView->setRenderHint(QPainter::Antialiasing);

    const int tileSize = 80;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QRectF square(col * tileSize, row * tileSize, tileSize, tileSize);
            auto *rect = scene->addRect(square);

            QColor color = (row + col) % 2 == 0 ? QColor(0xf0d9b5) : QColor(0xb58863);
            rect->setBrush(color);
        }
    }
    // Set fixed scene size to exactly fit the board
    scene->setSceneRect(0, 0, 8 * tileSize, 8 * tileSize);

    // Disable scrollbars
    ui->boardGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->boardGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Optional: Resize view to fit the scene exactly (if view size changes)
    ui->boardGraphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::placePiece(const QString &svgPath, PieceColor color, int row, int col) {
    const int tileSize = 80;
    auto *piece = new DraggablePiece(svgPath, color, row, col, tileSize);
    scene->addItem(piece);

    piece->setScale(tileSize / piece->boundingRect().width());

    qreal offsetX = (tileSize - piece->boundingRect().width() * piece->scale()) / 2;
    qreal offsetY = (tileSize - piece->boundingRect().height() * piece->scale()) / 2;

    piece->setPos(col * tileSize + offsetX, row * tileSize + offsetY);
    connect(piece, &DraggablePiece::pieceMoved,
            controller, &ChessController::onPieceMoved);
}
