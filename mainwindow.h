#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QThread>

#include "pointsgenerator.h"


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
    void addPointToScene(std::pair<double, double> point);
    void removePointsFromScene();


private:
    void initScene();



private:
    Ui::MainWindow *ui;
    PointsGenerator* m_pointsGenerator = nullptr;
    QThread  m_thread;
    QGraphicsScene* m_scene;
};
#endif // MAINWINDOW_H