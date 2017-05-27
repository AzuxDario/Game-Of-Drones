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

    void KeyPressed(Qt::Key key);
    void KeyReleased(Qt::Key key);

    bool IsKeyPressed(Qt::Key key);
};

#endif
