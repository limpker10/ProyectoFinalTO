#ifndef QLABELFACTORY_H
#define QLABELFACTORY_H

#include <QtWidgets>

class QLabelFactory
{
public:
    static QLabel* createLabel(QWidget* parent, const QString& imagePath, const QSize& size, const QPoint& position, const QString& imageId);
};

#endif // QLABELFACTORY_H
