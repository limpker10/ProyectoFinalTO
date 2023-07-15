#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Qmainwindow.h"
class GameState {
public:
    virtual void start(QMainWindow* mainWindow) = 0;
    virtual void end(QMainWindow* mainWindow) = 0;
};

#endif // GAMESTATE_H
