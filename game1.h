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
    void start() override;
    void end() override;
    ~Game1();

signals:
    void game1Signal();


private:
    Ui::Game1 *ui;

};

#endif // GAME1_H
