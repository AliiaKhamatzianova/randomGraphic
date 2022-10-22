#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void initCustomPlot();

private:
    Ui::MainWindow *ui;
    PointsGenerator m_pointsGenerator;
    QThread  m_thread;
};
#endif // MAINWINDOW_H
