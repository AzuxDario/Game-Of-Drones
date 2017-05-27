#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QVector>

class KeyboardManager
{
public:
    KeyboardManager();

    void KeyPressed(Qt::Key key);
    void KeyReleased(Qt::Key key);

    bool IsKeyPressed(Qt::Key key);
private:
    int state[256];
};

#endif
