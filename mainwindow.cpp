#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include "gamecontroller.h"

#include <QGraphicsView>
#include <QTimer>

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene,this)),
    game(new Gamecontroller(*scene,this))
{
    setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    setWindowTitle(tr("GreedySnake1.1"));

    aboutAction = new QAction(tr("Info"),this); //About 不能乱用
    aboutAction->setStatusTip(tr("View information about this game."));
    connect(aboutAction,&QAction::triggered,this,&MainWindow::showabout);

    pauseAction = new QAction(tr("&Pause"),this);
    pauseAction->setStatusTip(tr("Pause"));
    pauseAction->setShortcut(QKeySequence::Redo);
    connect(pauseAction,&QAction::triggered,game,&Gamecontroller::pause);

    diffAction = new QMenu();
    diffAction->setTitle("Difficulty");

    crazy = new QAction(tr("crazy"),diffAction);
    hard = new QAction(tr("hard"),diffAction);
    middle = new QAction(tr("middle"),diffAction);
    easy = new QAction(tr("easy"),diffAction);
    crazy->setStatusTip(tr("Set speed to crazy"));
    hard->setStatusTip(tr("Set speed to fast"));
    middle->setStatusTip(tr("Set speed to middle"));
    easy->setStatusTip(tr("Set speed to slow"));
    connect(crazy,&QAction::triggered,game,&Gamecontroller::changecrazy);
    connect(hard,&QAction::triggered,game,&Gamecontroller::changehard);
    connect(middle,&QAction::triggered,game,&Gamecontroller::changemiddle);
    connect(easy,&QAction::triggered,game,&Gamecontroller::changeeasy);

    QMenu *General = menuBar()->addMenu(tr("General"));
    General->addAction(aboutAction);
    General->addAction(pauseAction);
    General->addMenu(diffAction);
    diffAction->addAction(crazy);
    diffAction->addAction(hard);
    diffAction->addAction(middle);
    diffAction->addAction(easy);

    statusBar();

    setCentralWidget(view);
    resize(600,600);

    initScene();
    initSceneBackground();

    QTimer::singleShot(0,this,SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-110,-100,230,220);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);

    QPainter p(&bg);
    QPen pen(QColor("#dbf7cc"), 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setBrush(QBrush("#ffdaa6"));
    p.setPen(QPen(pen));
    p.drawRect(0,0,TILE_SIZE,TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

void MainWindow::showabout()
{
    QMessageBox::information(this, tr("Info"),tr("使用上下左右或WSAD都可以操控，空格暂停，初始难度为middle,退出程序后不保存记录。"));
}

void MainWindow::showpoint(int point,int maxpoint)
{
    QMessageBox::information(this, tr("Game over"),tr("Your point: %1\nHistory maxpoint: %2").arg(point).arg(maxpoint));
}
