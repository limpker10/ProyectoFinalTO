#ifndef GAME1_H
#define GAME1_H

#include "GameState.h"
#include <QWidget>
#include <QLabel>

namespace Ui {
class Game1;
}

class Game1 : public QWidget, public GameState
{
    Q_OBJECT

public:
    explicit Game1(QWidget *parent = nullptr);
    void start(QMainWindow* mainWindow) override;
    void end(QMainWindow* mainWindow) override;
    ~Game1();


private:
    Ui::Game1 *ui;
    QVector<QLabel*> imageLabels; // Vector para almacenar las etiquetas de las imágenes
    void setupImages(); // Función para configurar las imágenes
    void enableDragAndDrop(QLabel* label); // Función para habilitar "drag and drop" en una etiqueta

protected:
    bool eventFilter(QObject* object, QEvent* event) override;

};

#endif // GAME1_H
