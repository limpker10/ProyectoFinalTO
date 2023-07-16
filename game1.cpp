#include "game1.h"
#include "ui_game1.h"
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include "dragwidget.h"

Game1::Game1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game1)
{
    ui->setupUi(this);

    // Habilitar la funcionalidad de arrastrar y soltar en el marco

    //QHBoxLayout *horizontalLayout = new QHBoxLayout;
    //horizontalLayout->addWidget(new DragWidget);
    ui->horizontalLayout->addWidget(new DragWidget);
    //horizontalLayout->addWidget(new DragWidget);
    //this->setLayout(horizontalLayout);
}

Game1::~Game1()
{
    delete ui;
}

void Game1::start(QMainWindow* mainWindow)
{
    // Lógica específica para el estado Game1
    // ...
    mainWindow->setCentralWidget(this);
    this->show();
    qDebug() << "Iniciando el estado Game1";


    // Configurar las imágenes
    //setupImages();
}

void Game1::end(QMainWindow* mainWindow)
{
    // Lógica específica para finalizar el estado Game1
    // ...
    this->hide();
    qDebug() << "Finalizando el estado Game1";
}

void Game1::setupImages()
{

}

void Game1::dragEnterEvent(QDragEnterEvent *event)
{

}

void Game1::dragMoveEvent(QDragMoveEvent *event)
{

}

void Game1::dropEvent(QDropEvent *event)
{

}

void Game1::mousePressEvent(QMouseEvent *event)
{

}
