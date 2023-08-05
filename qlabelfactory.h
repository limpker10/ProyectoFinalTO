#ifndef QLABELFACTORY_H
#define QLABELFACTORY_H

#include "AbstractLabelFactory.h" // Incluimos la definición de la clase AbstractLabelFactory
#include <QtWidgets>

class QLabelFactory : public AbstractLabelFactory {
public:
    // Funcion para crear un QLabel como figura.
    // Recibe un puntero a QWidget como padre, la ruta de la imagen, y un ID de la imagen.
    QLabel* createFigureLabel(QWidget* parent, const QString& imagePath, const QString& imageId) override;

    // Funcion para crear un QLabel como caja.
    // Recibe un puntero a QWidget como padre, la ruta de la imagen, la posición y un ID de la imagen.
    QLabel* createBoxLabel(QWidget* parent, const QString& imagePath, QPoint& position, const QString& imageId) override;

private:
    // Funcion privada para crear un QLabel con propiedades comunes.
    // Recibe un puntero a QWidget como padre, la ruta de la imagen, el tamaño, la posición y un ID de la imagen.
    QLabel* createLabel(QWidget* parent, const QString& imagePath, const QSize& size, const QPoint& position, const QString& imageId);

    // Funcion privada para generar una posición aleatoria dentro del marco especificado (ancho y alto).
    QPoint randomPointWithinFrame(int width, int height);
};

#endif // QLABELFACTORY_H
