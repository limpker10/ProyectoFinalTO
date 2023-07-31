#include <QtWidgets>

#include "dragwidget.h"
#include <QMediaPlayer>
#include "qlabelfactory.h"
#include "SoundManager.h"

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{

    setupFrame();
    createFigures();
    createBoxes();
    SoundManager::instance().playBackgroundMusic("qrc:/sounds/game1_sound01.wav");
}

void DragWidget::setupFrame()
{
    setFrameStyle(QFrame::Box  | QFrame::Raised);
    setAcceptDrops(true);
}

void DragWidget::createFigures()
{
    QLabelFactory::createLabel(this, ":/images/circulo_red.png", QSize(100, 100), randomPointWithinFrame(), "cuadrado");
    QLabelFactory::createLabel(this, ":/images/triangulo.png", QSize(100, 100), randomPointWithinFrame(), "triangulo");
    QLabelFactory::createLabel(this, ":/images/circulo.png", QSize(100, 100), randomPointWithinFrame(), "circulo");
    QLabelFactory::createLabel(this, ":/images/circulo_red.png", QSize(100, 100), randomPointWithinFrame(), "cuadrado");
    QLabelFactory::createLabel(this, ":/images/triangulo.png", QSize(100, 100), randomPointWithinFrame(), "triangulo");
    QLabelFactory::createLabel(this, ":/images/circulo.png", QSize(100, 100), randomPointWithinFrame(), "circulo");

}

QPoint DragWidget::randomPointWithinFrame() {
    int margin = 10;  // Margen para evitar que las labels se posicionen en los bordes del frame
    int maxWidth = 601;
    int maxHeight = 400;
    int x = QRandomGenerator::global()->bounded(margin, maxWidth);
    int y = QRandomGenerator::global()->bounded(margin, maxHeight);
    return QPoint(x, y);
}
void DragWidget::createBoxes()
{
    int spacing = 20; // Espacio entre etiquetas
    int marginRight = 30; // Margen derecho
    int marginLeft = 400; // Margen derecho
    int marginTop = 0; // Margen superior

    // Obtenemos el tamaño de la ventana
    QSize windowSize = this->size();

    // Posicionamos la primera etiqueta en la parte superior derecha de la ventana
    QPoint position1(windowSize.width()+ 200 + marginLeft - marginRight, marginTop);

    // Para las siguientes etiquetas, ajustamos la posición verticalmente, sumando la altura de la etiqueta anterior y el espaciado
    QPoint position2(windowSize.width() + 200 + marginLeft - marginRight, position1.y() + 170 + spacing);
    QPoint position3(windowSize.width() + 200 + marginLeft - marginRight, position2.y() + 170 + spacing);

    QLabelFactory::createLabel(this, ":/images/box.png", QSize(200, 170), position1, "box");
    QLabelFactory::createLabel(this, ":/images/box.png", QSize(200, 170), position2, "box");
    QLabelFactory::createLabel(this, ":/images/box.png", QSize(200, 170), position3, "box");

}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
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

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
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

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->position().toPoint() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        auto [isOverBox, boxLabel] = findBoxLabel(newIcon->geometry().center());

        if (isOverBox && boxLabel) {
            handleItemDroppedOnBox(newIcon,pixmap);

        } else {
            qDebug() << "La nueva imagen no está encima de un QLabel con el ID 'box'.";
        }

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

std::pair<bool, QLabel*> DragWidget::findBoxLabel(const QPoint& position)
{
    QList<QLabel*> childLabels = findChildren<QLabel*>();
    QLabel* boxLabel = nullptr;
    bool isOverBox = std::any_of(childLabels.begin(), childLabels.end(), [&](QLabel* label) {
        if (label->property("imageId") == "box" && label->geometry().contains(position)) {
            boxLabel = label;
            return true;
        }
        return false;
    });

    return { isOverBox, boxLabel };
}

void DragWidget::handleItemDroppedOnBox(QLabel* newIcon, QPixmap pixmap)
{
    QPixmap scaledPixmap = pixmap.scaled(QSize(pixmap.width() / 2, pixmap.height() / 2), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    newIcon->setPixmap(scaledPixmap);

    qDebug() << "La nueva imagen está encima de un QLabel con el ID 'box'.";

    // Emitir la señal cuando se cumple la condición
    emit itemDroppedOnBox();

    // Reproduce un sonido
    SoundManager::instance().playSound("qrc:/sounds/sound_2.wav");
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
    if (!child || child->property("imageId").toString() == "box") {
        return;
    }

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
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    drag->exec(Qt::MoveAction);
    child->close();
}
