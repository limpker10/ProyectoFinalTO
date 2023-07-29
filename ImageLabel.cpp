// imagelabel.cpp
#include "imagelabel.h"
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QMouseEvent>

ImageLabel::ImageLabel(const QPixmap& pixmap, const QPoint& position, const QString& imageId, QWidget* parent)
    : QLabel(parent), imageId(imageId)
{
    setPixmap(pixmap);
    move(position);
    show();
    setAttribute(Qt::WA_DeleteOnClose);

    setAcceptDrops(true);
}

void ImageLabel::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void ImageLabel::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void ImageLabel::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        // Tu lógica para procesar el dropEvent específico del ImageLabel
        // ...

        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void ImageLabel::mousePressEvent(QMouseEvent* event)
{
    QLabel* child = static_cast<QLabel*>(childAt(event->position().toPoint()));
    if (!child || child->property("imageId").toString() == "box") {
        return;
    }

    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());

    QMimeData* mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag* drag = new QDrag(this);
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
