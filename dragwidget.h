#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include "qlabel.h"
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
    void createFigures();
    void createBoxes();
    std::pair<bool, QLabel*> findBoxLabel(const QPoint&);
    void handleItemDroppedOnBox(QLabel*,QPixmap);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    QPoint randomPointWithinFrame();

signals:
    void itemDroppedOnBox();
};

#endif // DRAGWIDGET_H
