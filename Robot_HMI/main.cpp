#include "login.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogIn w;
    QScreen *desktop = QApplication::primaryScreen();

    int WIDTH = 400;
    int HEIGHT = 250;

    QRect screen_geometry = desktop->geometry();

    int screenWidth = screen_geometry.width();
    int screenHeight = screen_geometry.height();

    int x = (screenWidth - WIDTH) / 2;
    int y = (screenHeight - HEIGHT) / 2;

    w.resize(WIDTH, HEIGHT);
    w.move( x, y );
    w.show();
    return a.exec();
}
