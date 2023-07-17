#include "game1.h"
#include "ui_game1.h"
#include "dragwidget.h"

Game1::Game1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game1)
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(new DragWidget);
    connect(ui->pushButtonSalir, &QPushButton::clicked, this, &Game1::end);
}

Game1::~Game1()
{
    delete ui;
}

void Game1::start()
{

    this->show();
    qDebug() << "Iniciando Game1";
}

void Game1::end()
{
    qDebug() << "Finalizando Game1";
    emit game1Signal();
    delete this;
}

