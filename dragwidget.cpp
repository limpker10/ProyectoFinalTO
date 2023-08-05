#include <QtWidgets>

#include "dragwidget.h"
#include <QMediaPlayer>
#include "qlabelfactory.h"
#include "SoundManager.h"

// Constructor de DragWidget
DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent) // Heredando de QFrame
{
    // Configurando el marco y permitiendo el arrastrar y soltar
    setupFrame();

    // Creando figuras para ser utilizadas en la interfaz
    createFigures();

    // Creando cajas (método no mostrado en el fragmento de código proporcionado)
    createBoxes();

    // Reproduciendo la música de fondo específica para este widget
    SoundManager::instance().playBackgroundMusic("qrc:/sounds/game1_sound01.wav");
}

// Configuración del marco y habilitación de la funcionalidad de arrastrar y soltar
void DragWidget::setupFrame()
{
    setFrameStyle(QFrame::Box  | QFrame::Raised); // Estableciendo el estilo del marco
    setAcceptDrops(true); // Permitiendo el arrastrar y soltar en este marco
}

// Creando figuras utilizando una fábrica de etiquetas (QLabel)
void DragWidget::createFigures()
{
    // Creando diferentes figuras con identificadores específicos
    // Utilizando la ruta a las imágenes de las figuras
    labelFactory.createFigureLabel(this, ":/images/circulo_red.png", "circulo");
    labelFactory.createFigureLabel(this, ":/images/cuadrado.png", "cuadrado");
    labelFactory.createFigureLabel(this, ":/images/triangulo.png",  "triangulo");
    labelFactory.createFigureLabel(this, ":/images/circulo.png",  "circulo");
    labelFactory.createFigureLabel(this, ":/images/circulo_red.png", "cuadrado");
    labelFactory.createFigureLabel(this, ":/images/triangulo.png", "triangulo");
    labelFactory.createFigureLabel(this, ":/images/cuadrado.png", "cuadrado");
    labelFactory.createFigureLabel(this, ":/images/cuadrado.png", "cuadrado");
}


void DragWidget::createBoxes()
{
    int spacing = 20; // Espacio entre etiquetas
    int marginRight = 30; // Margen derecho
    int marginLeft = 400; // Margen derecho
    int marginTop = 0; // Margen superior

    // Obtenemos el tamaño de la ventana
    QSize windowSize = this->size();

    // parte superior derecha de la ventana
    QPoint position1(windowSize.width()+ 200 + marginLeft - marginRight, marginTop);

    // Ajuste posición verticalmente, sumando la altura de la etiqueta anterior y el espaciado
    QPoint position2(windowSize.width() + 200 + marginLeft - marginRight, position1.y() + 170 + spacing);
    QPoint position3(windowSize.width() + 200 + marginLeft - marginRight, position2.y() + 170 + spacing);

    labelFactory.createBoxLabel(this, ":/images/box.png", position1,"box");
    labelFactory.createBoxLabel(this, ":/images/box.png", position2,"box");
    labelFactory.createBoxLabel(this, ":/images/box.png", position3,"box");

}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    // Verificamos si los datos MIME del evento contienen el formato application/x-dnditemdata
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        // Si el evento proviene de este widget, configuramos la acción de soltar como MoveAction y aceptamos el evento.
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            // Si el evento proviene de otra fuente, aceptamos la acción propuesta.
            event->acceptProposedAction();
        }
    } else {
        // Si los datos MIME no contienen el formato esperado, ignoramos el evento de arrastre.
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    // Verificamos si los datos MIME del evento contienen el formato application/x-dnditemdata
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        // Si el evento proviene de este widget, configuramos la acción de soltar como MoveAction y aceptamos el evento.
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            // Si el evento proviene de otra fuente, aceptamos la acción propuesta.
            event->acceptProposedAction();
        }
    } else {
        // Si los datos MIME no contienen el formato esperado, ignoramos el evento de arrastre.
        event->ignore();
    }
}


void DragWidget::dropEvent(QDropEvent *event)
{
    // Comprueba si los datos arrastrados tienen el formato correcto
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        // Extrae los datos (pixmap e información de desplazamiento) del evento
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        // es un punto que representa la diferencia entre la posición del cursor y
        // la esquina superior izquierda de la imagen que está siendo arrastrada con esto
        // nos aseguramos que la imagen se coloque en la posición correcta cuando se suelte.
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset; // Deserializa los datos

        // Crea una nueva etiqueta para representar el objeto soltado
        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        // Posiciona en el punto de caída
        // La resta del offset asegura que la etiqueta se coloque en la posición correcta dentro del widget.
        newIcon->move(event->position().toPoint() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        // Comprueba si el objeto se ha soltado sobre una etiqueta de caja
        // Determinar si la etiqueta ha sido soltada sobre una etiqueta de caja en el widget.
        auto [isOverBox, boxLabel] = findBoxLabel(newIcon->geometry().center());

        if (isOverBox && boxLabel) {
            // Si se ha soltado sobre una caja, maneja el evento correspondiente
            handleItemDroppedOnBox(newIcon, pixmap);
        } else {
            // Si no, escribe un mensaje en la consola de depuración
            qDebug() << "La nueva imagen no está encima de un QLabel con el ID 'box'.";
        }

        // Define la acción de caída y acepta el evento
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        // Ignora el evento si los datos arrastrados no tienen el formato correcto
        event->ignore();
    }
}



std::pair<bool, QLabel*> DragWidget::findBoxLabel(const QPoint& position)
{
    //El QPoint se utiliza para representar una posición específica dentro del widget
    // Encuentra todos los hijos QLabel de este widget
    QList<QLabel*> childLabels = findChildren<QLabel*>();

    QLabel* boxLabel = nullptr; // Puntero para almacenar la etiqueta de caja encontrada, si existe

    // Utiliza std::any_of para determinar si alguna de las etiquetas es una "caja" en la posición dada
    bool isOverBox = std::any_of(childLabels.begin(), childLabels.end(), [&](QLabel* label) {
        if (label->property("imageId") == "box" && label->geometry().contains(position)) {
            boxLabel = label; // Si se encuentra la caja, asigna la etiqueta a boxLabel
            return true; // Retorna verdadero para indicar que se encontró una caja en la posición
        }
        return false; // Retorna falso si esta etiqueta no es una caja en la posición dada
    });

    return { isOverBox, boxLabel }; // Retorna un par que contiene un booleano y un puntero a QLabel
}


void DragWidget::handleItemDroppedOnBox(QLabel* newIcon, QPixmap pixmap)
{
    // Escalamos la imagen a la mitad de su tamaño original con su relación de aspecto preservada
    QPixmap scaledPixmap = pixmap.scaled(QSize(pixmap.width() / 2, pixmap.height() / 2), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    newIcon->setPixmap(scaledPixmap);

    // Imprimimos un mensaje de depuración indicando que la nueva imagen está encima de un QLabel con el ID 'box'
    qDebug() << "La nueva imagen está encima de un QLabel con el ID 'box'.";

        // Emitimos una señal para notificar que se ha soltado un ítem en la caja
        emit itemDroppedOnBox();

    // Reproducimos un sonido utilizando el SoundManager, se asume que existe el archivo de sonido "qrc:/sounds/sound_2.wav"
    SoundManager::instance().playSound("qrc:/sounds/sound_2.wav");
}


void DragWidget::mousePressEvent(QMouseEvent *event)
{
    // Buscamos si hay algún QLabel en la posición donde se ha hecho clic
    QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));

    // Si no se encontró ningún QLabel o si el QLabel tiene la propiedad "imageId" igual a "box", no hacemos nada y retornamos.
    // Esto significa que no queremos permitir arrastrar la imagen que está encima del QLabel con ID "box".
    if (!child || child->property("imageId").toString() == "box") {
        return;
    }

    // Obtenemos el QPixmap del QLabel que se ha seleccionado para arrastrar
    QPixmap pixmap = child->pixmap();

    // Creamos un QByteArray para almacenar los datos de los ítems a ser arrastrados
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());

    // Creamos un objeto QMimeData para almacenar los datos MIME del ítem a ser arrastrado
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    // Creamos un objeto QDrag para iniciar la operación de arrastrar y soltar
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->position().toPoint() - child->pos());

    // Creamos una copia temporal del QPixmap para mostrarla como el objeto arrastrado
    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);

    // Pintamos una capa semitransparente en el QPixmap para simular el efecto de "arrastrar"
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    // Establecemos la copia temporal del QPixmap como la imagen del QLabel original
    child->setPixmap(tempPixmap);

    // Iniciamos la operación de arrastrar y soltar con el modo "MoveAction"
    drag->exec(Qt::MoveAction);

    // Cerramos el QLabel original después de que se ha completado la operación de arrastrar y soltar
    child->close();
}

