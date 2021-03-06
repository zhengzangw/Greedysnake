#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class QGraphicsScene;
class QGraphicsView;
class Gamecontroller;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showpoint(int,int);

private slots:
    void adjustViewSize();

private:
    Ui::MainWindow *ui;
    void showabout();
    QAction *pauseAction,*aboutAction,*easy,*middle,*hard,*crazy;
    QMenu *diffAction;

    void initScene();
    void initSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;

    Gamecontroller *game;
};

#endif // MAINWINDOW_H
