#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include "Draggable.h"
#include "FigureManager.h"
#include "qlabelfactory.h"

// Clase DragWidget, hereda de QFrame (para la representación de un marco),
// FigureManager (para la gestión de figuras), y Draggable (para habilidades de arrastrar y soltar)
class DragWidget : public QFrame, public FigureManager, public Draggable
{
    Q_OBJECT // Macro para soportar signals y slots en Qt
    QLabelFactory labelFactory; // Instancia de una fábrica de etiquetas para crear QLabel

public:
    explicit DragWidget(QWidget *parent = nullptr); // Constructor

    // Implementacion de metodos de FigureManager
    void createFigures() override;
    void createBoxes() override;
    std::pair<bool, QLabel*> findBoxLabel(const QPoint&) override;
    void handleItemDroppedOnBox(QLabel*, QPixmap) override;

    // Implementacion de metodos de Draggable
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void setupFrame(); // Método para configurar el marco
    void mousePressEvent(QMouseEvent *event) override; // Manejador de evento cuando se presiona algun label

signals:
    void itemDroppedOnBox(); // Señal que se emite cuando un label se ha soltado en una caja
};

#endif // DRAGWIDGET_H
