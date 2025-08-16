#pragma once
#include <QDialog>
#include "../controller/ChessController.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class PromotionDialog;
}

QT_END_NAMESPACE

class PromotionDialog final : public QDialog {
    Q_OBJECT

public:
    explicit PromotionDialog(ChessColor color, QWidget *parent = nullptr);

    ~PromotionDialog() override;

    [[nodiscard]] PromotionType selectedType() const { return choice_; }

private slots:
    void chooseQueen();

    void chooseRook();

    void chooseBishop();

    void chooseKnight();

private:
    Ui::PromotionDialog *ui_;
    PromotionType choice_ = PromotionType::kQueen;

    void setIconsForColor(ChessColor color);
};
