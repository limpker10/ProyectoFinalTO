#include "qlabelfactory.h"

// Crea una etiqueta (QLabel) para una figura con un tamaño y posición aleatoria dentro de un marco
QLabel* QLabelFactory::createFigureLabel(QWidget* parent, const QString& imagePath, const QString& imageId) {
    return createLabel(parent, imagePath, QSize(100, 100), randomPointWithinFrame(601,400), imageId);
}

// Crea una etiqueta (QLabel) para una caja con un tamaño y posición específicos
QLabel* QLabelFactory::createBoxLabel(QWidget* parent, const QString& imagePath, QPoint& position, const QString& imageId) {
    return createLabel(parent, imagePath, QSize(200, 170), position, imageId);
}

// Método genérico para crear una etiqueta (QLabel) con una imagen, tamaño y posición determinados
QLabel* QLabelFactory::createLabel(QWidget* parent, const QString& imagePath, const QSize& size, const QPoint& position, const QString& imageId)
{
    QLabel *label = new QLabel(parent);
    // Establece la imagen de la etiqueta y escala manteniendo la relación de aspecto
    label->setPixmap(QPixmap(imagePath).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // Mueve la etiqueta a la posición especificada
    label->move(position);
    // Muestra la etiqueta
    label->show();
    // Establece el atributo para eliminar la etiqueta al cerrar
    label->setAttribute(Qt::WA_DeleteOnClose);
    // Establece una propiedad personalizada para almacenar una identificación de imagen
    label->setProperty("imageId", imageId);

    return label;
}

// Genera un punto aleatorio dentro de un marco dado, manteniendo un margen de 10 píxeles
QPoint QLabelFactory::randomPointWithinFrame(int maxWidth, int maxHeight) {
    int margin = 10;
    int x = QRandomGenerator::global()->bounded(margin, maxWidth);
    int y = QRandomGenerator::global()->bounded(margin, maxHeight);
    return QPoint(x, y);
}
