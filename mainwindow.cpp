#include "mainwindow.h"
#include "game1.h"
#include "qpushbutton.h"
#include "ui_mainwindow.h"
#include "SoundManager.h"

// Constructor de MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), // Heredando de QMainWindow
    ui(new Ui::MainWindow), // Inicializando la interfaz de usuario (UI)
    currentState() // Inicializando el estado actual del juego
{
    // Configurando la UI
    ui->setupUi(this);

    // Conectando el botón a la funcion que maneja el click del botón Game1
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onGame1ButtonClicked);

    // Iniciando la música de fondo con la instancia de SoundManager
    SoundManager::instance().playBackgroundMusic("qrc:/sounds/soundambient.wav");
}

// Destructor de MainWindow
MainWindow::~MainWindow()
{
    // Eliminando la UI al destruir el objeto
    delete ui;
}

// Manejando el evento de clic en el botón Game1
void MainWindow::onGame1ButtonClicked()
{
    // Creando una nueva instancia del juego 1
    Game1* game1 = new Game1();

    // Asignando el juego 1 como estado actual
    currentState = game1;

    // Conectando la señal de juego 1 con la funcion onGame1SignalReceived
    connect(game1, &Game1::game1Signal, this, &MainWindow::onGame1SignalReceived);

    // Iniciando el estado actual y finalizando la ventana principal
    currentState->start();
    end();
}

// Cambiando el estado actual del juego
void MainWindow::switchToState(GameState* state)
{
    // Si hay un estado actual, terminarlo
    if (currentState) {
        currentState->end();
    }

    // Asignar el nuevo estado y comenzar
    currentState = state;
    currentState->start();
}

// Iniciando la ventana principal
void MainWindow::start()
{
    // Mostrando el widget
    this->show();

    // Imprimiendo en la consola de depuración
    qDebug() << "Iniciando MainWindow";
}

// Finalizando la ventana principal
void MainWindow::end()
{
    // Ocultando el widget
    this->hide();

    // Imprimiendo en la consola de depuración
    qDebug() << "Ocultando MainWindow";
}

// Manejando la señal recibida desde el juego 1
void MainWindow::onGame1SignalReceived()
{
    // Imprimiendo en la consola de depuración
    qDebug() << "Señal recibida desde Game1";

    // Iniciando la ventana principal
    start();
}

