#include "KeyboardManager/keyboardmanager.h"

KeyboardManager::KeyboardManager()
{
    for(int i=0; i<256; i++)
        state[i] = false;
}

void KeyboardManager::KeyPressed(Qt::Key key)
{
    int keyCode = (int)key;
    if(keyCode < 256)
        state[keyCode] = true;
}

void KeyboardManager::KeyReleased(Qt::Key key)
{
    int keyCode = (int)key;
    if(keyCode < 256)
        state[keyCode] = false;
}

bool KeyboardManager::IsKeyPressed(Qt::Key key)
{
    return state[(int)key];
}
