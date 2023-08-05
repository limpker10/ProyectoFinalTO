#include "game1.h"
#include "ui_game1.h"
#include "dragwidget.h"

// Constructor de Game1
Game1::Game1(QWidget *parent) :
    QWidget(parent), // Heredando de QWidget
    ui(new Ui::Game1) // Inicializando la interfaz de usuario (UI)
{
    // Configurando la UI
    ui->setupUi(this);

    // Creando un nuevo widget para la funcion de arrastrar y soltar
    DragWidget* dragWidget = new DragWidget(this);

    // Estableciendo la politica de tamaño del widget para que se expanda
    dragWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Añadiendo el widget a la disposición horizontal de la UI
    ui->horizontalLayout->addWidget(dragWidget);

    // Conectando el botón Salir a la funcion de terminar el juego
    connect(ui->pushButtonSalir, &QPushButton::clicked, this, &Game1::end);

    // Conectando la señal de que un elemento ha sido soltado en el DragWidget con la funcion de manejar dicha acción en Game1
    connect(dragWidget, &DragWidget::itemDroppedOnBox, this, &Game1::handleItemDroppedOnBox);
}

// Destructor de Game1
Game1::~Game1()
{
    // Eliminando la UI al destruir el objeto
    delete ui;
}

// Iniciando el juego
void Game1::start()
{
    // Mostrando el widget
    this->show();

    // Imprimiendo en la consola de depuración
    qDebug() << "Iniciando Game1";
}

// Finalizando el juego
void Game1::end()
{
    // Imprimiendo en la consola de depuración
    qDebug() << "Finalizando Game1";

    // Emite una señal de que el juego ha terminado o esta saliendo del mismo
    emit game1Signal();

    // Destruye el objeto actual
    delete this;
}

// Manejando el evento de que un elemento ha sido soltado en el DragWidget
void Game1::handleItemDroppedOnBox()
{
    // Obteniendo el puntaje actual del widget de texto
    int currentScore = ui->plainTextEditScore->toPlainText().toInt();

    // Incrementando el puntaje
    currentScore++;

    // Actualizando el puntaje en la UI
    ui->plainTextEditScore->setPlainText(QString::number(currentScore));
}

