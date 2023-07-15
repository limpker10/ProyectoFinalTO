#include "game1.h"
#include "ui_game1.h"
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

Game1::Game1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game1)
{
    ui->setupUi(this);
}

Game1::~Game1()
{
    delete ui;
}

void Game1::start(QMainWindow* mainWindow) {
    // Lógica específica para el estado Game1
    // ...
    mainWindow->setCentralWidget(this);
    this->show();
    qDebug() << "Iniciando el estado Game1";
    // Configurar las imágenes
    setupImages();
}

void Game1::end(QMainWindow* mainWindow) {
    // Lógica específica para finalizar el estado Game1
    // ...
    this->hide();
    qDebug() << "Finalizando el estado Game1";
}

void Game1::setupImages()
{
    // Crear y configurar las etiquetas de las imágenes
    QLabel* imageLabel1 = new QLabel(this);

    // Configurar la imagen para imageLabel1
    QPixmap cuadrado(":/cuadrado.png"); // Cargar el recurso "cuadrado.png" desde el archivo de recursos
    ui->label->setPixmap(cuadrado);
    imageLabel1->setPixmap(cuadrado);

    QLabel* imageLabel2 = new QLabel(this);
    // Configurar la imagen para imageLabel2
    // ...

    // Agregar las etiquetas de las imágenes al vector
    imageLabels.push_back(imageLabel1);
    imageLabels.push_back(ui->label_2);

    // Habilitar "drag and drop" en cada etiqueta
    for (QLabel* label : imageLabels) {
        enableDragAndDrop(label);
    }

    // Posicionar y mostrar las etiquetas de las imágenes
    // ...
}

void Game1::enableDragAndDrop(QLabel* label)
{
    label->setAcceptDrops(true);
    label->installEventFilter(this);
}

bool Game1::eventFilter(QObject* object, QEvent* event)
{
    QLabel* label = qobject_cast<QLabel*>(object);
    if (label && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() & Qt::LeftButton) {
            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            // Configura los datos MIME necesarios para el "drag and drop"
            // ...
            drag->setMimeData(mimeData);
            drag->exec(Qt::MoveAction);
        }
        return true;
    }
    else if (label && event->type() == QEvent::DragEnter) {
        QDragEnterEvent* dragEnterEvent = static_cast<QDragEnterEvent*>(event);
        dragEnterEvent->acceptProposedAction();
        return true;
    }
    else if (label && event->type() == QEvent::Drop) {
        QDropEvent* dropEvent = static_cast<QDropEvent*>(event);
        const QMimeData* mimeData = dropEvent->mimeData();
        // Realiza las acciones necesarias cuando se suelta el objeto arrastrado
        // ...
        dropEvent->acceptProposedAction();
        return true;
    }
    return false;
}

