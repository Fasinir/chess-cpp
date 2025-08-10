#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QGraphicsRectItem>
#include <QTime>
#include <QRandomGenerator>

#include "PromotionDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    controller_ = new ChessController(this);

    connect(ui_->startLocalGameButton, &QPushButton::clicked, this, &MainWindow::startLocalGame);
    connect(ui_->startEngineGameButton, &QPushButton::clicked, this, &MainWindow::startEngineGame);
    connect(ui_->colorComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updatePlayer2ColorLabel);
    connect(ui_->startGameButton, &QPushButton::clicked, this, &MainWindow::proceedToGamePage);
    connect(controller_, &ChessController::boardUpdated, this, &MainWindow::drawBoardFromModel);
    connect(controller_, &ChessController::promotionRequested, this, &MainWindow::handlePromotionRequested);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::startLocalGame() {
    showConfigScreen(GameMode::Local);
}

void MainWindow::startEngineGame() {
    showConfigScreen(GameMode::Engine);
}

void MainWindow::showConfigScreen(GameMode mode) {
    current_game_mode_ = mode;
    ui_->stackedWidget->setCurrentWidget(ui_->configPage);

    bool is_engine_game = (mode == GameMode::Engine);
    ui_->chessEngineComboBox->setVisible(is_engine_game);
    ui_->playerTwoLineEdit->setVisible(!is_engine_game);
    ui_->playerTwoColorLabel->setVisible(!is_engine_game);
}

void MainWindow::updatePlayer2ColorLabel() const {
    const QString kChoice = ui_->colorComboBox->currentText();

    if (kChoice == "White") {
        ui_->playerTwoColorLabel->setText("Black");
    } else if (kChoice == "Black") {
        ui_->playerTwoColorLabel->setText("White");
    } else {
        ui_->playerTwoColorLabel->setText("Random color");
    }
}

void MainWindow::proceedToGamePage() {
    GameSettings settings;

    settings.mode_ = current_game_mode_;
    settings.player1_name_ = ui_->playerOneLineEdit->text();
    settings.base_time_ = ui_->timeEdit->time();
    settings.increment_seconds_ = ui_->incrementSpinBox->value();

    if (current_game_mode_ == GameMode::Engine) {
        settings.player2_name_ = ui_->chessEngineComboBox->currentText();
    } else {
        settings.player2_name_ = ui_->playerTwoLineEdit->text();
    }

    QString color_choice = ui_->colorComboBox->currentText();
    if (color_choice == "White") {
        settings.white_player_name_ = settings.player1_name_;
        settings.black_player_name_ = settings.player2_name_;
    } else if (color_choice == "Black") {
        settings.white_player_name_ = settings.player2_name_;
        settings.black_player_name_ = settings.player1_name_;
    } else {
        if (QRandomGenerator::global()->bounded(2) == 0) {
            settings.white_player_name_ = settings.player1_name_;
            settings.black_player_name_ = settings.player2_name_;
        } else {
            settings.white_player_name_ = settings.player2_name_;
            settings.black_player_name_ = settings.player1_name_;
        }
    }

    // Store or pass to controller
    this->game_settings_ = settings;

    // Update UI
    ui_->whitePlayerNameLabel->setText(settings.white_player_name_);
    ui_->blackPlayerNameLabel->setText(settings.black_player_name_);

    QString formatted_time = settings.base_time_.toString("hh:mm:ss");
    ui_->whitePlayerTimerLabel->setText(formatted_time);
    ui_->blackPlayerTimerLabel->setText(formatted_time);

    ui_->stackedWidget->setCurrentWidget(ui_->gamePage);
    drawBoardTiles();
    drawBoardFromModel();
    controller_->startGame(settings);
}


void MainWindow::drawBoardTiles() {
    if (scene_) delete scene_;
    scene_ = new QGraphicsScene(this);
    ui_->boardGraphicsView->setScene(scene_);
    ui_->boardGraphicsView->setRenderHint(QPainter::Antialiasing);

    const int kTileSize = 80;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QRectF square(col * kTileSize, row * kTileSize, kTileSize, kTileSize);
            auto *rect = scene_->addRect(square);

            QColor color = (row + col) % 2 == 0 ? QColor(0xf0d9b5) : QColor(0xb58863);
            rect->setBrush(color);
        }
    }
    // Set fixed scene size to exactly fit the board
    scene_->setSceneRect(0, 0, 8 * kTileSize, 8 * kTileSize);

    // Disable scrollbars
    ui_->boardGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->boardGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Optional: Resize view to fit the scene exactly (if view size changes)
    ui_->boardGraphicsView->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::placePiece(const QString &svg_path, PieceColor color, int row, int col) {
    const int kTileSize = 80;
    auto *piece = new DraggablePiece(svg_path, color, row, col, kTileSize);
    scene_->addItem(piece);

    piece->setScale(kTileSize / piece->boundingRect().width());

    qreal offset_x = (kTileSize - piece->boundingRect().width() * piece->scale()) / 2;
    qreal offset_y = (kTileSize - piece->boundingRect().height() * piece->scale()) / 2;

    piece->setPos(col * kTileSize + offset_x, (7 - row) * kTileSize + offset_y);
    connect(piece, &DraggablePiece::pieceMoved,
            controller_, &ChessController::onPieceMoved);
    connect(controller_, &ChessController::illegalMoveAttempted, piece, &DraggablePiece::revertToOriginalPosition);
}

void MainWindow::drawBoardFromModel() {
    // Remove all pieces, but leave the board tiles
    for (auto item: scene_->items()) {
        auto *piece = dynamic_cast<DraggablePiece *>(item);
        if (piece) {
            scene_->removeItem(piece);
            delete piece;
        }
    }

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto opt_figure = controller_->getBoard()->figureAt(col, row);
            if (!opt_figure.has_value()) continue;

            auto fig = opt_figure.value();
            QString color_prefix = (fig->getColor() == ChessColor::WHITE) ? "white" : "black";
            QString piece_name = QString::fromStdString(fig->getName());
            QString path = QString("../assets/%1_%2.svg").arg(color_prefix, piece_name);

            PieceColor gui_color = (fig->getColor() == ChessColor::WHITE) ? PieceColor::White : PieceColor::Black;
            placePiece(path, gui_color, row, col);
        }
    }
}

void MainWindow::handlePromotionRequested(const Coordinates kCoordinates, const ChessColor kColor) {
    if (PromotionDialog dialog(kColor, this); dialog.exec() == QDialog::Accepted) {
        controller_->promote(kCoordinates, dialog.selectedType());
    }
}
