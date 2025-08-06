#include "PromotionDialog.h"
#include "ui_PromotionDialog.h"

PromotionDialog::PromotionDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::PromotionDialog), choice(PromotionType::QUEEN) {
    ui->setupUi(this);

    connect(ui->queenButton, &QPushButton::clicked, this, &PromotionDialog::chooseQueen);
    connect(ui->rookButton, &QPushButton::clicked, this, &PromotionDialog::chooseRook);
    connect(ui->bishopButton, &QPushButton::clicked, this, &PromotionDialog::chooseBishop);
    connect(ui->knightButton, &QPushButton::clicked, this, &PromotionDialog::chooseKnight);
}

PromotionDialog::~PromotionDialog() {
    delete ui;
}

PromotionType PromotionDialog::selectedType() const {
    return choice;
}

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
