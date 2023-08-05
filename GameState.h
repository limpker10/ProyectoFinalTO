#ifndef GAMESTATE_H
#define GAMESTATE_H

// Definición de la interfaz GameState
class GameState {
public:
    //Las clases derivadas deben implementar estas funciones segun sus necesidades.

    // Funcion virtual pura para iniciar el estado del juego.
    virtual void start() = 0;

    // Funcion virtual pura para finalizar el estado del juego.
    virtual void end() = 0;
};

#endif // GAMESTATE_H
