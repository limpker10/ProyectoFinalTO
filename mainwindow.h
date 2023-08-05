#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameState.h" // Incluimos la definición de la clase GameState
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public GameState
{
    Q_OBJECT // Macro para habilitar la funcionalidad de signals y slots en la clase

public:
    // Constructor de la clase MainWindow, puede recibir un puntero a QWidget como parametro (es el padre del widget)
    MainWindow(QWidget *parent = nullptr);

    // funcion para cambiar al estado especificado, toma un puntero a GameState como parametro
    void switchToState(GameState* state);

    // Destructor de la clase MainWindow
    ~MainWindow();

private slots:
    // slot que se ejecuta cuando se hace clic en el botón "Game1Button"
    void onGame1ButtonClicked();

    // slot que se ejecuta cuando se recibe una señal relacionada con el juego 1
    void onGame1SignalReceived();

private:
    // Funcion privada para iniciar el juego
    void start();

    // Funcion privada para finalizar el juego
    void end();

    Ui::MainWindow *ui; // Puntero al objeto de la interfaz de usuario de la ventana principal
    GameState* currentState; // Puntero al estado actual del juego (objeto GameState)
};

#endif // MAINWINDOW_H
