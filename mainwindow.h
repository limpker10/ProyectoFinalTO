#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameState.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGame1ButtonClicked();
    void onGame2ButtonClicked();

private:
    void switchToState(GameState* state);
    Ui::MainWindow *ui;
    GameState* currentState;
};
#endif // MAINWINDOW_H
