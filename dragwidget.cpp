#include <QtWidgets>

#include "dragwidget.h"
#include <QMediaPlayer>
#include "qlabelfactory.h"
#include "SoundManager.h"

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{

    setupFrame();
    setupAnimation();
    createFigures();
    createBoxes();
    SoundManager::instance().playBackgroundMusic("qrc:/sounds/soundambient.wav");
}

void DragWidget::setupFrame()
{
    setFrameStyle(QFrame::Box  | QFrame::Raised);
    setAcceptDrops(true);
}

void DragWidget::setupAnimation()
{
    shrinkAnimation = new QPropertyAnimation(this, "geometry");
    shrinkAnimation->setDuration(1000);
}

void DragWidget::createFigures()
{
    QLabelFactory::createLabel(this, ":/images/circulo_red.png", QSize(100, 100), QPoint(79, 120), "cuadrado");
    QLabelFactory::createLabel(this, ":/images/triangulo.png", QSize(100, 100), QPoint(200, 110), "triangulo");
    QLabelFactory::createLabel(this, ":/images/circulo.png", QSize(100, 100), QPoint(130, 240), "circulo");
}

void DragWidget::createBoxes()
{
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignRight);

    QLabel *label1 = QLabelFactory::createLabel(this, ":/images/box.png", QSize(200, 170), QPoint(), "box");
    QLabel *label2 = QLabelFactory::createLabel(this, ":/images/box.png", QSize(200, 170), QPoint(), "box");
    QLabel *label3 = QLabelFactory::createLabel(this, ":/images/box.png", QSize(200, 170), QPoint(), "box");

    vLayout->addWidget(label1);
    vLayout->addWidget(label2);
    vLayout->addWidget(label3);

    setLayout(vLayout);
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
        QLabel* boxLabel = nullptr;
        auto isOverBox = std::any_of(childLabels.begin(), childLabels.end(), [&](QLabel *label) {
            if(label->property("imageId") == "box" && label->geometry().contains(newIcon->geometry())){
                boxLabel = label;
                return true;
            }
            return false;
        });

        if (isOverBox && boxLabel) {
            QPixmap scaledPixmap = pixmap.scaled(QSize(pixmap.width() / 2, pixmap.height() / 2), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            newIcon->setPixmap(scaledPixmap);
            shrinkAnimation->setTargetObject(newIcon);
            shrinkAnimation->setStartValue(newIconRect);
            shrinkAnimation->setEndValue(QRect(newIconRect.x(), newIconRect.y(), newIconRect.width() / 2, newIconRect.height() / 2));

            qDebug() << "La nueva imagen está encima de un QLabel con el ID 'box'.";
                        // Iniciar la animacion
                        shrinkAnimation->start();
            // Emitir la señal cuando se cumple la condición
            emit itemDroppedOnBox();

            // Reproduce un sonido
            SoundManager::instance().playSound("qrc:/sounds/sound_2.wav");

            // Elimina el QLabel que está sobre el box
            //boxLabel->deleteLater();
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
