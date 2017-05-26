#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Game of Drones");
    //w.show();
    w.showFullScreen(); //Dzięki temu będzie fullscreen

    return a.exec();
}
