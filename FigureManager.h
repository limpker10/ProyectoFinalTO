#ifndef FIGUREMANAGER_H
#define FIGUREMANAGER_H
#include <QLabel>
#include <QPoint>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class FigureManager
{
public:
    virtual ~FigureManager() {}

    virtual void createFigures() = 0;
    virtual void createBoxes() = 0;
    virtual std::pair<bool, QLabel*> findBoxLabel(const QPoint&) = 0;
    virtual void handleItemDroppedOnBox(QLabel*, QPixmap) = 0;
    virtual QPoint randomPointWithinFrame() = 0;
};
#endif // FIGUREMANAGER_H
