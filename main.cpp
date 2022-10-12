#include "MainWindow.h"
#include <QApplication>
#include "QTableWidget"
#include <QLineEdit>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
