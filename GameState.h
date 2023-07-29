#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
    virtual void start() = 0;
    virtual void end() = 0;
};

#endif // GAMESTATE_H
