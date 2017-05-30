#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QVector>
#include <QMap>

class KeyboardManager
{
private:
    QMap<Qt::Key, bool> keyMap;

public:
    KeyboardManager();

    void keyPressed(Qt::Key key);
    void keyReleased(Qt::Key key);

    bool isKeyPressed(Qt::Key key);
};

#endif
