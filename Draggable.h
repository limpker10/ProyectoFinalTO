#ifndef DRAGGABLE_H
#define DRAGGABLE_H
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

// Interfaz pura Draggable
class Draggable
{
public:
    virtual ~Draggable() {} // Destructor virtual
    // metodos que deben ser implementados por cualquier clase que herede de Draggable
    // metodo puramente virtual para manejar el evento de ingreso de un objeto arrastrable
    virtual void dragEnterEvent(QDragEnterEvent *event) = 0;

    // metodo puramente virtual para manejar el evento de movimiento de un objeto arrastrable
    virtual void dragMoveEvent(QDragMoveEvent *event) = 0;

    // metodo puramente virtual para manejar el evento de soltar un objeto arrastrable
    virtual void dropEvent(QDropEvent *event) = 0;
};

#endif // DRAGGABLE_H
