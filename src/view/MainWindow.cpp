#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QGraphicsRectItem>
#include <QTime>
#include <QRandomGenerator>

#include "PromotionDialog.h"

const QColor MainWindow::kHighlightColor = QColor(0, 200, 0, 90);
const QColor MainWindow::kWhiteFieldColor = QColor(0xf0d9b5);
const QColor MainWindow::kBlackFieldColor = QColor(0xb58863);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    controller_ = new ChessController(this);

    connect(ui_->startLocalGameButton, &QPushButton::clicked, this, &MainWindow::showConfigScreen);
    connect(ui_->colorComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updatePlayer2ColorLabel);
    connect(ui_->startGameButton, &QPushButton::clicked, this, &MainWindow::proceedToGamePage);
    connect(controller_, &ChessController::boardUpdated, this, &MainWindow::drawBoardFromModel);
    connect(controller_, &ChessController::promotionRequested, this, &MainWindow::handlePromotionRequested);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::showLegalMoveHighlights(int from_row, int from_col) {
    clearLegalMoveHighlights();
    auto dests = controller_->legalDestinationsFrom(from_col, from_row);

    for (const auto &c: dests) {
        int col = c.getX();
        int row = c.getY();

        QRectF square(col * kTileSize, (7 - row) * kTileSize, kTileSize, kTileSize);
        auto *rect = scene_->addRect(square, Qt::NoPen, kHighlightColor);
        rect->setZValue(0.5);
        move_highlights_.push_back(rect);
    }
}

void MainWindow::clearLegalMoveHighlights() {
    for (auto *it: move_highlights_) {
        scene_->removeItem(it);
        delete it;
    }
    move_highlights_.clear();
}

void MainWindow::showConfigScreen() {
    ui_->stackedWidget->setCurrentWidget(ui_->configPage);
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

    settings.player1_name_ = ui_->playerOneLineEdit->text();
    settings.player2_name_ = ui_->playerTwoLineEdit->text();

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

    this->game_settings_ = settings;

    ui_->whitePlayerNameLabel->setText(settings.white_player_name_);
    ui_->blackPlayerNameLabel->setText(settings.black_player_name_);

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

    scene_->installEventFilter(this);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QRectF square(col * kTileSize, row * kTileSize, kTileSize, kTileSize);
            auto *rect = scene_->addRect(square);

            QColor color = (row + col) % 2 == 0 ? kWhiteFieldColor : kBlackFieldColor;
            rect->setBrush(color);
        }
    }
    // Set fixed scene size to exactly fit the board
    scene_->setSceneRect(0, 0, 8 * kTileSize, 8 * kTileSize);

    ui_->boardGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->boardGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui_->boardGraphicsView->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::placePiece(const QString &svg_path, const ChessColor &color, int row, int col) {
    auto *piece = new DraggablePiece(svg_path, color, row, col, kTileSize);
    scene_->addItem(piece);

    piece->setScale(kTileSize / piece->boundingRect().width());

    qreal offset_x = (kTileSize - piece->boundingRect().width() * piece->scale()) / 2;
    qreal offset_y = (kTileSize - piece->boundingRect().height() * piece->scale()) / 2;

    piece->setPos(col * kTileSize + offset_x, (7 - row) * kTileSize + offset_y);
    connect(piece, &DraggablePiece::pieceMoved,
            controller_, &ChessController::onPieceMoved);
    connect(controller_, &ChessController::illegalMoveAttempted, piece, &DraggablePiece::revertToOriginalPosition);
    connect(piece, &DraggablePiece::pieceSelected,
            this, [this](int r, int c) { showLegalMoveHighlights(r, c); });
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == scene_ && event->type() == QEvent::GraphicsSceneMousePress) {
        auto *ev = static_cast<QGraphicsSceneMouseEvent *>(event);

        // Check what was clicked at that scene position
        const auto items_at_pos = scene_->items(ev->scenePos());

        bool clicked_piece = false;
        for (QGraphicsItem *it: items_at_pos) {
            if (qgraphicsitem_cast<DraggablePiece *>(it)) {
                clicked_piece = true;
                break;
            }
        }

        if (!clicked_piece) {
            clearLegalMoveHighlights();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::drawBoardFromModel() {
    clearLegalMoveHighlights();
    for (auto item: scene_->items()) {
        auto *piece = dynamic_cast<DraggablePiece *>(item);
        if (piece) {
            scene_->removeItem(piece);
            delete piece;
        }
    }

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto opt_figure = controller_->getBoard()->figureAt(Coordinates(col, row));
            if (!opt_figure.has_value()) continue;

            auto fig = opt_figure.value();
            QString color_prefix = (fig->getColor() == ChessColor::kWhite) ? "white" : "black";
            QString piece_name = QString::fromStdString(fig->getName());
            QString path = QString("../assets/%1_%2.svg").arg(color_prefix, piece_name);

            ChessColor piece_color = fig->getColor();
            placePiece(path, piece_color, row, col);
        }
    }
}

void MainWindow::handlePromotionRequested(const Coordinates &coordinates, const ChessColor &color) {
    if (PromotionDialog dialog(color, this); dialog.exec() == QDialog::Accepted) {
        controller_->promote(coordinates, dialog.selectedType());
    }
}
