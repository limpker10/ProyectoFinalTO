#include "game1.h"
#include "ui_game1.h"
#include "dragwidget.h"

Game1::Game1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game1)
{
    ui->setupUi(this);
    DragWidget* dragWidget = new DragWidget(this);
    dragWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->horizontalLayout->addWidget(dragWidget);
    //ui->horizontalLayout->setStretchFactor(dragWidget, 1);

    connect(ui->pushButtonSalir, &QPushButton::clicked, this, &Game1::end);
    // Conectar la señal itemDroppedOnBox() de DragWidget a la ranura handleItemDroppedOnBox() de Game1
    connect(dragWidget, &DragWidget::itemDroppedOnBox, this, &Game1::handleItemDroppedOnBox);
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

void Game1::handleItemDroppedOnBox()
{
    // Aumentar el puntaje en el QPlainTextEdit de la interfaz de usuario (UI)
    int currentScore = ui->plainTextEditScore->toPlainText().toInt();
    currentScore++;
    ui->plainTextEditScore->setPlainText(QString::number(currentScore));
}
