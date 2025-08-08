// PromotionDialog.h
#pragma once
#include <QDialog>
#include "../controller/ChessController.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class PromotionDialog;
}

QT_END_NAMESPACE

class PromotionDialog : public QDialog {
    Q_OBJECT

public:
    explicit PromotionDialog(ChessColor color, QWidget *parent = nullptr);

    ~PromotionDialog() override;

    [[nodiscard]] PromotionType selectedType() const { return choice; }

private slots:
    void chooseQueen();

    void chooseRook();

    void chooseBishop();

    void chooseKnight();

private:
    Ui::PromotionDialog *ui;
    PromotionType choice = PromotionType::QUEEN;

    void setIconsForColor(ChessColor color);
};
