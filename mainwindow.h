#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameState.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,public GameState
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void switchToState(GameState* state);
    ~MainWindow();

private slots:
    void onGame1ButtonClicked();
    void onGame1SignalReceived();

private:
    void start();
    void end();
    Ui::MainWindow *ui;
    GameState* currentState;
};
#endif // MAINWINDOW_H
