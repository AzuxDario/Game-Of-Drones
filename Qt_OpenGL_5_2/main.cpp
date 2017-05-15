#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Moja piąta aplikacja w Qt z OpenGL'em");
    w.show();

    return a.exec();
}
