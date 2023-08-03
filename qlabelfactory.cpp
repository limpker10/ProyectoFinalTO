#include "qlabelfactory.h"

QLabel* QLabelFactory::createFigureLabel(QWidget* parent, const QString& imagePath, const QString& imageId) {
    return createLabel(parent, imagePath, QSize(100, 100), randomPointWithinFrame(601,400), imageId);
}

QLabel* QLabelFactory::createBoxLabel(QWidget* parent, const QString& imagePath, QPoint& position, const QString& imageId) {
    return createLabel(parent, imagePath, QSize(200, 170), position, imageId);
}

QLabel* QLabelFactory::createLabel(QWidget* parent, const QString& imagePath, const QSize& size, const QPoint& position, const QString& imageId)
{
    QLabel *label = new QLabel(parent);
    label->setPixmap(QPixmap(imagePath).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label->move(position);
    label->show();
    label->setAttribute(Qt::WA_DeleteOnClose);
    label->setProperty("imageId", imageId);

    return label;
}

QPoint QLabelFactory::randomPointWithinFrame(int maxWidth, int maxHeight) {
    int margin = 10;
    int x = QRandomGenerator::global()->bounded(margin, maxWidth);
    int y = QRandomGenerator::global()->bounded(margin, maxHeight);
    return QPoint(x, y);
}
