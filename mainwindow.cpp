#include "mainwindow.h"
#include "game1.h"
#include "qpushbutton.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentState()
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onGame1ButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGame1ButtonClicked()
{

    Game1* game1 = new Game1();
    currentState = game1;
    connect(game1, &Game1::game1Signal, this, &MainWindow::onGame1SignalReceived);
    currentState->start();
    end();
}

void MainWindow::switchToState(GameState* state)
{
    if (currentState) {
        currentState->end();
    }

    currentState = state;
    currentState->start();
}

void MainWindow::start()
{

    this->show();
    qDebug() << "Iniciando MainWindow";
}

void MainWindow::end()
{
    this->hide();
    qDebug() << "Ocultando MainWindow";

}

void MainWindow::onGame1SignalReceived()
{
    qDebug() << "Señal recibida desde Game1";
    start();
}
