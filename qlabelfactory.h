#ifndef QLABELFACTORY_H
#define QLABELFACTORY_H

#include "AbstractLabelFactory.h"
#include <QtWidgets>

class QLabelFactory : public AbstractLabelFactory {
public:
    QLabel* createFigureLabel(QWidget* parent, const QString& imagePath, const QString& imageId) override;
    QLabel* createBoxLabel(QWidget* parent, const QString& imagePath,QPoint& position,const QString& imageId) override;
private:
    QLabel* createLabel(QWidget* parent, const QString& imagePath, const QSize& size, const QPoint& position, const QString& imageId);
    QPoint randomPointWithinFrame(int , int );

};


#endif // QLABELFACTORY_H
