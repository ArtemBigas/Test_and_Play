//#include "MainWindow.h"
#include "Dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog mainwindow;
    mainwindow.setWindowTitle("Test and Play");
    mainwindow.setWindowFlags(mainwindow.windowFlags() | Qt::WindowMaximizeButtonHint);
    mainwindow.show();
    return a.exec();
}
