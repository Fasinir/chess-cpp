#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QGraphicsRectItem>
#include <QTime>
#include <QDebug>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    controller = new ChessController(this);

    connect(ui->startLocalGameButton, &QPushButton::clicked, this, &MainWindow::startLocalGame);
    connect(ui->startEngineGameButton, &QPushButton::clicked, this, &MainWindow::startEngineGame);
    connect(ui->colorComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updatePlayer2ColorLabel);
    connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::proceedToGamePage);
    connect(controller, &ChessController::boardUpdated, this, [this]() {
        this->drawBoardFromModel(); // We'll implement this
    });
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
    GameSettings settings;

    settings.mode = currentGameMode;
    settings.player1Name = ui->playerOneLineEdit->text();
    settings.baseTime = ui->timeEdit->time();
    settings.incrementSeconds = ui->incrementSpinBox->value();

    if (currentGameMode == GameMode::Engine) {
        settings.player2Name = ui->chessEngineComboBox->currentText();
    } else {
        settings.player2Name = ui->playerTwoLineEdit->text();
    }

    QString colorChoice = ui->colorComboBox->currentText();
    if (colorChoice == "White") {
        settings.whitePlayerName = settings.player1Name;
        settings.blackPlayerName = settings.player2Name;
    } else if (colorChoice == "Black") {
        settings.whitePlayerName = settings.player2Name;
        settings.blackPlayerName = settings.player1Name;
    } else {
        if (QRandomGenerator::global()->bounded(2) == 0) {
            settings.whitePlayerName = settings.player1Name;
            settings.blackPlayerName = settings.player2Name;
        } else {
            settings.whitePlayerName = settings.player2Name;
            settings.blackPlayerName = settings.player1Name;
        }
    }

    // Store or pass to controller
    this->gameSettings = settings;

    // Update UI
    ui->whitePlayerNameLabel->setText(settings.whitePlayerName);
    ui->blackPlayerNameLabel->setText(settings.blackPlayerName);

    QString formattedTime = settings.baseTime.toString("hh:mm:ss");
    ui->whitePlayerTimerLabel->setText(formattedTime);
    ui->blackPlayerTimerLabel->setText(formattedTime);

    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    drawChessBoard();
    drawBoardFromModel();
    controller->startGame(settings);
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

    piece->setPos(col * tileSize + offsetX, (7 - row) * tileSize + offsetY);
    connect(piece, &DraggablePiece::pieceMoved,
            controller, &ChessController::onPieceMoved);
    connect(controller, &ChessController::illegalMoveAttempted, piece, &DraggablePiece::revertToOriginalPosition);
}

void MainWindow::drawBoardFromModel() {
    // Remove all pieces, but leave the board tiles
    for (auto item: scene->items()) {
        auto *piece = dynamic_cast<DraggablePiece *>(item);
        if (piece) {
            scene->removeItem(piece);
            delete piece;
        }
    }

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto optFigure = controller->getBoard()->figureAt(col, row);
            if (!optFigure.has_value()) continue;

            auto fig = optFigure.value();
            QString colorPrefix = (fig->getColor() == ChessColor::WHITE) ? "white" : "black";
            QString pieceName = QString::fromStdString(fig->getName());
            QString path = QString("../assets/%1_%2.svg").arg(colorPrefix, pieceName);

            PieceColor guiColor = (fig->getColor() == ChessColor::WHITE) ? PieceColor::White : PieceColor::Black;
            placePiece(path, guiColor, row, col);
        }
    }
}
