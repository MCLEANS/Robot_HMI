#include "login.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogIn w;
    QDesktopWidget *desktop = QApplication::desktop();

    int WIDTH = 400;
    int HEIGHT = 250;

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    int x = (screenWidth - WIDTH) / 2;
    int y = (screenHeight - HEIGHT) / 2;

    w.resize(WIDTH, HEIGHT);
    w.move( x, y );
    w.show();
    return a.exec();
}
