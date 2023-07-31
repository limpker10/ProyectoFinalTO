#ifndef DRAGGABLE_H
#define DRAGGABLE_H
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

class Draggable
{
public:
    virtual ~Draggable() {}

    virtual void dragEnterEvent(QDragEnterEvent *event) = 0;
    virtual void dragMoveEvent(QDragMoveEvent *event) = 0;
    virtual void dropEvent(QDropEvent *event) = 0;
};
#endif // DRAGGABLE_H
