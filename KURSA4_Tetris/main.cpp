#include <QtWidgets>

#include <stdlib.h>

#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //TetrixWindow window;
    TetrixWindow::Instance()->show();
    int ret =  app.exec();
    TetrixWindow::Instance()->updateUserName();
    TetrixWindow::Instance()->saveLog();
    return ret;
}
