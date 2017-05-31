#include "KeyboardManager/keyboardmanager.h"

KeyboardManager::KeyboardManager()
{
    keyMap.insert(Qt::Key_W, false);
    keyMap.insert(Qt::Key_A, false);
    keyMap.insert(Qt::Key_S, false);
    keyMap.insert(Qt::Key_D, false);
    keyMap.insert(Qt::Key_Q, false);
    keyMap.insert(Qt::Key_E, false);
    keyMap.insert(Qt::Key_Up, false);
    keyMap.insert(Qt::Key_Down, false);
    keyMap.insert(Qt::Key_Left, false);
    keyMap.insert(Qt::Key_Right, false);
    keyMap.insert(Qt::Key_Space, false);
}

void KeyboardManager::keyPressed(Qt::Key key)
{
    if(keyMap.find(key) != keyMap.end())
    {
        keyMap.insert(key,true);
    }
}

void KeyboardManager::keyReleased(Qt::Key key)
{
    if(keyMap.find(key) != keyMap.end())
    {
        keyMap.insert(key,false);
    }
}

bool KeyboardManager::isKeyPressed(Qt::Key key)
{
    return keyMap.value(key);
}
