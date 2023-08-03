#ifndef ABSTRACTLABELFACTORY_H
#define ABSTRACTLABELFACTORY_H
#include <QLabel>
#include <QWidget>

class AbstractLabelFactory {
public:
    virtual QLabel* createFigureLabel(QWidget* parent, const QString& imagePath, const QString& imageId) = 0;
    virtual QLabel* createBoxLabel(QWidget* parent, const QString& imagePath, QPoint& position,const QString& imageId) = 0;
};
#endif // ABSTRACTLABELFACTORY_H
