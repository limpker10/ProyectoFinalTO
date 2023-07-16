#include "game1.h"
#include "qdrag.h"
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
    ui->frame->setAcceptDrops(true);
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(new DragWidget);
    horizontalLayout->addWidget(new DragWidget);
    this->setLayout(horizontalLayout);
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
    // Configurar la imagen para la etiqueta label
    QPixmap cuadrado(":/images/cuadrado.png"); // Cargar el recurso "cuadrado.png" desde el archivo de recursos

    ui->label->setPixmap(cuadrado);
    ui->label->setScaledContents(true);
    ui->label->setAttribute(Qt::WA_DeleteOnClose);
}

void Game1::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Game1::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Game1::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(ui->frame);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->position().toPoint() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            // Verificar si la imagen se movió al marco
            if (ui->frame->geometry().contains(event->pos())) {
                qDebug() << "La imagen se movió al marco.";
            }
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Game1::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
    if (!child)
        return;

    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->position().toPoint() - child->pos());

    QPixmap tempPixmap = pixmap;

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
