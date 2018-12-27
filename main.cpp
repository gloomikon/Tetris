#include <QtWidgets>

#include <stdlib.h>

#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TetrixWindow window;
    window.show();
    return app.exec();
}
