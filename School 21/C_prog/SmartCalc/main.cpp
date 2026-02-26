
#include "mainwindow.h"

#include <QApplication>


Engine *engine;
Graphic *graphic;
Credit *credit;
MainWindow *w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Engine engine;
    Graphic graphic;
    Credit credit;
    MainWindow w;
    ::engine = &engine;
    ::graphic = &graphic;
    ::credit = &credit;
    ::w = &w;
    w.show();
    return a.exec();

}
