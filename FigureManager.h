#ifndef FIGUREMANAGER_H
#define FIGUREMANAGER_H
#include <QLabel>
#include <QPoint>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

// Clase FigureManager, una interfaz pura para manejar figuras y cajas en una aplicación gráfica
class FigureManager
{
public:
    virtual ~FigureManager() {} // Destructor virtual

    // metodos que deben ser implementado por cualquier clase que herede de FigureManager

    // metodo puramente virtual para crear figuras
    virtual void createFigures() = 0;

    // metodo puramente virtual para crear cajas
    virtual void createBoxes() = 0;

    // metodo puramente virtual para encontrar una etiqueta de caja en una ubicación dada
    // Devuelve un par que contiene un booleano y un puntero QLabel
    virtual std::pair<bool, QLabel*> findBoxLabel(const QPoint&) = 0;

    // metodo puramente virtual para manejar un artículo que ha sido soltado en una caja
    virtual void handleItemDroppedOnBox(QLabel*, QPixmap) = 0;

};
#endif // FIGUREMANAGER_H
