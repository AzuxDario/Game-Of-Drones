#include "KeyboardManager/keyboardmanager.h"

KeyboardManager::KeyboardManager()
{
    keyMap.insert(Qt::Key_W, false);
    keyMap.insert(Qt::Key_A, false);
    keyMap.insert(Qt::Key_S, false);
    keyMap.insert(Qt::Key_D, false);
    keyMap.insert(Qt::Key_Q, false);
    keyMap.insert(Qt::Key_E, false);
}

void KeyboardManager::KeyPressed(Qt::Key key)
{
    if(keyMap.find(key) != keyMap.end())
    {
        keyMap.insert(key,true);
    }
}

void KeyboardManager::KeyReleased(Qt::Key key)
{
    if(keyMap.find(key) != keyMap.end())
    {
        keyMap.insert(key,false);
    }
}

bool KeyboardManager::IsKeyPressed(Qt::Key key)
{
    return keyMap.value(key);
}
