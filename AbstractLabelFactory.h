#ifndef ABSTRACTLABELFACTORY_H
#define ABSTRACTLABELFACTORY_H
#include <QLabel>
#include <QWidget>

// Interfaz pura AbstractLabelFactory
class AbstractLabelFactory {
public:
    // Metodos que deben ser implementado por cualquier clase que herede de AbstractLabelFactory
    // Metodo puramente virtual para crear una etiqueta (QLabel) para una figura

    virtual QLabel* createFigureLabel(QWidget* parent, const QString& imagePath, const QString& imageId) = 0;

    // Metodo puramente virtual para crear una etiqueta (QLabel) para una caja

    virtual QLabel* createBoxLabel(QWidget* parent, const QString& imagePath, QPoint& position, const QString& imageId) = 0;
};

#endif // ABSTRACTLABELFACTORY_H
