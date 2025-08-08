#include "PromotionDialog.h"
#include "ui_PromotionDialog.h"
#include <QIcon>
#include <QSize>

PromotionDialog::PromotionDialog(ChessColor color, QWidget *parent)
    : QDialog(parent), ui(new Ui::PromotionDialog) {
    ui->setupUi(this);
    setWindowTitle("Choose promotion");

    // Hook up button clicks
    connect(ui->queenButton, &QPushButton::clicked, this, &PromotionDialog::chooseQueen);
    connect(ui->rookButton, &QPushButton::clicked, this, &PromotionDialog::chooseRook);
    connect(ui->bishopButton, &QPushButton::clicked, this, &PromotionDialog::chooseBishop);
    connect(ui->knightButton, &QPushButton::clicked, this, &PromotionDialog::chooseKnight);

    // Apply colored icons
    setIconsForColor(color);
}

PromotionDialog::~PromotionDialog() { delete ui; }

void PromotionDialog::setIconsForColor(ChessColor color) {
    const QString prefix = (color == ChessColor::WHITE) ? "white" : "black";
    const auto size = QSize(64, 64); // tweak if needed

    ui->queenButton->setIcon(QIcon(QString("../assets/%1_queen.svg").arg(prefix)));
    ui->rookButton->setIcon(QIcon(QString("../assets/%1_rook.svg").arg(prefix)));
    ui->bishopButton->setIcon(QIcon(QString("../assets/%1_bishop.svg").arg(prefix)));
    ui->knightButton->setIcon(QIcon(QString("../assets/%1_knight.svg").arg(prefix)));

    ui->queenButton->setIconSize(size);
    ui->rookButton->setIconSize(size);
    ui->bishopButton->setIconSize(size);
    ui->knightButton->setIconSize(size);
}

// Slots
void PromotionDialog::chooseQueen() {
    choice = PromotionType::QUEEN;
    accept();
}

void PromotionDialog::chooseRook() {
    choice = PromotionType::ROOK;
    accept();
}

void PromotionDialog::chooseBishop() {
    choice = PromotionType::BISHOP;
    accept();
}

void PromotionDialog::chooseKnight() {
    choice = PromotionType::KNIGHT;
    accept();
}
