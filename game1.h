#ifndef GAME1_H
#define GAME1_H

#include "GameState.h" // Incluimos la definicion de la clase GameState
#include <QWidget>
#include <QLabel>

namespace Ui {
class Game1;
}

class Game1 : public QWidget, public GameState
{
    Q_OBJECT // Macro para habilitar la funcionalidad de signals y slots en la clase

public:
    // Constructor de la clase Game1, puede recibir un puntero a QWidget como parametro (es el padre del widget)
    explicit Game1(QWidget *parent = nullptr);

    // Funcion para iniciar el estado del juego, implementacion de la interfaz GameState.
    void start() override;

    // Funcion para finalizar el estado del juego, implementacion de la interfaz GameState.
    void end() override;

    // Destructor de la clase Game1
    ~Game1();

signals:
    // Señal emitida cuando ocurre un evento específico en el juego 1
    void game1Signal();

private:
    Ui::Game1 *ui; // Puntero al objeto de la interfaz de usuario de Game1
private slots:
    // Ranura que se ejecuta cuando se suelta un ítem en la caja
    void handleItemDroppedOnBox();
};

#endif // GAME1_H
