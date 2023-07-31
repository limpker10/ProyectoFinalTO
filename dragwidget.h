#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include "Draggable.h"
#include "FigureManager.h"

class DragWidget : public QFrame, public FigureManager, public Draggable
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);

    // Implementación de métodos de FigureManager
    void createFigures() override;
    void createBoxes() override;
    std::pair<bool, QLabel*> findBoxLabel(const QPoint&) override;
    void handleItemDroppedOnBox(QLabel*, QPixmap) override;
    QPoint randomPointWithinFrame() override;

    // Implementación de métodos de Draggable
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void setupFrame();
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void itemDroppedOnBox();
};

#endif // DRAGWIDGET_H
