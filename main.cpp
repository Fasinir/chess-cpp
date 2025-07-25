#include "src/view/MainWindow.h"

#include <QApplication>

#include "LocalPrintTesting.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    LocalPrintTesting::legalMovesForColor();
    return a.exec();
}
