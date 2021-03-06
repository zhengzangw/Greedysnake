#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QMessageBox>

#include "snake.h"
#include "mainwindow.h"

class QGraphicsScene;
class QKeyEvent;

class Snake;
class Food;
class Wall;

class Gamecontroller : public QObject
{
    Q_OBJECT
public:
    Gamecontroller(QGraphicsScene &scene, MainWindow *parent=0);
    ~Gamecontroller();

    void snakeAteFood(Snake *snake, Food *food);
    void snakeHitWall(Snake *snake, Wall *wall);
    void snakeAteItself(Snake *snake);

    void changehard();
    void changemiddle();
    void changeeasy();
    void changecrazy();
    void statechanged();
    int point,maxpoint=0;

public slots:
    void pause();
    void resume();
    void gameOver();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();

    QTimer timer;
    QGraphicsScene &scene;

    Snake *snake;
    Wall *wall;
    Snake::Direction previous = Snake::NoMove;
    MainWindow *p;
    bool changed=true;
};

#endif // GAMECONTROLLER_H
