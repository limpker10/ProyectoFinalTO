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
    imageLabel1->setPixmap(cuadrado);

    QLabel* imageLabel2 = new QLabel(this);
    // Configurar la imagen para imageLabel2
    // ...

    // Agregar las etiquetas de las imágenes al vector
    imageLabels.push_back(imageLabel1);
    imageLabels.push_back(imageLabel2);

    // Habilitar "drag and drop" en cada etiqueta
    for (QLabel* label : imageLabels) {
        enableDragAndDrop(label);
    }

    // Posicionar y mostrar las etiquetas de las imágenes
    int x = 10;
    int y = 10;
    int spacing = 10;
    int labelWidth = 100;
    int labelHeight = 100;

    for (QLabel* label : imageLabels) {
        label->setGeometry(x, y, labelWidth, labelHeight);
        label->show();

        // Actualizar las coordenadas para la siguiente etiqueta
        x += labelWidth + spacing;
    }
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
            // Establecer los datos de arrastre en mimeData
            // ...
            drag->setMimeData(mimeData);
            drag->exec(Qt::MoveAction);
        }
        return true;
    }
    return false;
}
