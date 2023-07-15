#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game1.h"
#include "qpushbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentState(nullptr)
{
    ui->setupUi(this);
    // ...
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onGame1ButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGame1ButtonClicked()
{
    if (currentState) {
        currentState->end(this);
    }

    currentState = new Game1();
    currentState->start(this);
}

void MainWindow::onGame2ButtonClicked()
{
    if (currentState) {
        currentState->end(this);
    }

    currentState = new Game1();
    currentState->start(this);
}

void MainWindow::switchToState(GameState* state)
{
    if (currentState) {
        currentState->end(this);
    }

    currentState = state;
    currentState->start(this);
}


