#include <QtWidgets>

#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    //setMinimumSize(200, 200);
    setFrameStyle(QFrame::Box  | QFrame::Raised);
    setAcceptDrops(true);

    shrinkAnimation = new QPropertyAnimation(this, "geometry");
    shrinkAnimation->setDuration(1000);

    QLabel *cuadrado = new QLabel(this);
    cuadrado->setPixmap(QPixmap(":/images/circulo_red.png").scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    cuadrado->move(79, 120);
    cuadrado->show();
    cuadrado->setAttribute(Qt::WA_DeleteOnClose);
    cuadrado->setProperty("imageId", "cuadrado");

    QLabel *triangulo = new QLabel(this);
    triangulo->setPixmap(QPixmap(":/images/triangulo.png").scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    triangulo->move(200, 110);
    triangulo->show();
    triangulo->setAttribute(Qt::WA_DeleteOnClose);
    triangulo->setProperty("imageId", "triangulo");

    QLabel *circulo = new QLabel(this);
    circulo->setPixmap(QPixmap(":/images/circulo.png").scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    circulo->move(130, 240);
    circulo->show();
    circulo->setAttribute(Qt::WA_DeleteOnClose);
    circulo->setProperty("imageId", "circulo");

    QLabel *box = new QLabel(this);
    box->setPixmap(QPixmap(":/images/box.png").scaled(QSize(200, 170), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    int box1X = width() - box->width() - 10; // Posicionar a la derecha
    int box1Y = 10; // Posicionar en la parte superior
    box->move(box1X, box1Y);
    box->show();
    box->setAttribute(Qt::WA_DeleteOnClose);
    box->setProperty("imageId", "box");

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

        QRect newIconRect = newIcon->geometry();

        QList<QLabel *> childLabels = findChildren<QLabel *>();
        auto isOverBox = std::any_of(childLabels.begin(), childLabels.end(), [&](QLabel *label) {
            return label->property("imageId") == "box" && label->geometry().contains(newIcon->geometry());
        });

        if (isOverBox) {
            QPixmap scaledPixmap = pixmap.scaled(QSize(pixmap.width() / 2, pixmap.height() / 2), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            newIcon->setPixmap(scaledPixmap);
            shrinkAnimation->setTargetObject(newIcon);
            shrinkAnimation->setStartValue(newIconRect);
            shrinkAnimation->setEndValue(QRect(newIconRect.x(), newIconRect.y(), newIconRect.width() / 2, newIconRect.height() / 2));

            qDebug() << "La nueva imagen está encima de un QLabel con el ID 'box'.";
            // Iniciar la animacion
            shrinkAnimation->start();
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
