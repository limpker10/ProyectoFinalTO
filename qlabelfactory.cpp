#include "qlabelfactory.h"

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
