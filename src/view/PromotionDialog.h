#ifndef PROMOTIONDIALOG_H
#define PROMOTIONDIALOG_H

#include <QDialog>
#include "../controller/ChessController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PromotionDialog; }
QT_END_NAMESPACE

class PromotionDialog : public QDialog {
    Q_OBJECT

public:
    explicit PromotionDialog(QWidget *parent = nullptr);
    ~PromotionDialog();

    PromotionType selectedType() const;

    private slots:
        void chooseQueen();
    void chooseRook();
    void chooseBishop();
    void chooseKnight();

private:
    Ui::PromotionDialog *ui;
    PromotionType choice;
};

#endif // PROMOTIONDIALOG_H
