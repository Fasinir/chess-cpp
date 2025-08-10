#include "PromotionDialog.h"
#include "ui_PromotionDialog.h"
#include <QIcon>
#include <QSize>

PromotionDialog::PromotionDialog(ChessColor color, QWidget *parent)
    : QDialog(parent), ui_(new Ui::PromotionDialog) {
    ui_->setupUi(this);
    setWindowTitle("Choose promotion");

    // Hook up button clicks
    connect(ui_->queenButton, &QPushButton::clicked, this, &PromotionDialog::chooseQueen);
    connect(ui_->rookButton, &QPushButton::clicked, this, &PromotionDialog::chooseRook);
    connect(ui_->bishopButton, &QPushButton::clicked, this, &PromotionDialog::chooseBishop);
    connect(ui_->knightButton, &QPushButton::clicked, this, &PromotionDialog::chooseKnight);

    // Apply colored icons
    setIconsForColor(color);
}

PromotionDialog::~PromotionDialog() { delete ui_; }

void PromotionDialog::setIconsForColor(ChessColor color) {
    QString prefix = (color == ChessColor::WHITE) ? "white" : "black";
    auto size = QSize(64, 64); // tweak if needed

    ui_->queenButton->setIcon(QIcon(QString("../assets/%1_queen.svg").arg(prefix)));
    ui_->rookButton->setIcon(QIcon(QString("../assets/%1_rook.svg").arg(prefix)));
    ui_->bishopButton->setIcon(QIcon(QString("../assets/%1_bishop.svg").arg(prefix)));
    ui_->knightButton->setIcon(QIcon(QString("../assets/%1_knight.svg").arg(prefix)));

    ui_->queenButton->setIconSize(size);
    ui_->rookButton->setIconSize(size);
    ui_->bishopButton->setIconSize(size);
    ui_->knightButton->setIconSize(size);
}

// Slots
void PromotionDialog::chooseQueen() {
    choice_ = PromotionType::QUEEN;
    accept();
}

void PromotionDialog::chooseRook() {
    choice_ = PromotionType::ROOK;
    accept();
}

void PromotionDialog::chooseBishop() {
    choice_ = PromotionType::BISHOP;
    accept();
}

void PromotionDialog::chooseKnight() {
    choice_ = PromotionType::KNIGHT;
    accept();
}
