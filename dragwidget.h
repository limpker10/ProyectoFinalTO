#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include "qpropertyanimation.h"
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class DragWidget : public QFrame
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);

private:
    QPropertyAnimation* shrinkAnimation;
    void setupFrame();
    void setupAnimation();
    void createFigures();
    void createBoxes();
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void itemDroppedOnBox();
};

#endif // DRAGWIDGET_H
