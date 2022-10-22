#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

#include "Defines.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initCustomPlot();

    m_pointsGenerator = new PointsGenerator();
    m_pointsGenerator->moveToThread(&m_thread);
    m_thread.start();
    connect(ui->startBtn, &QToolButton::clicked, m_pointsGenerator, &PointsGenerator::startGenerate);
    connect(ui->pauseBtn, &QToolButton::clicked, m_pointsGenerator, &PointsGenerator::pauseGenerate, Qt::ConnectionType::DirectConnection);
    connect(ui->stopBtn, &QToolButton::clicked, m_pointsGenerator, &PointsGenerator::stopGenerate, Qt::ConnectionType::DirectConnection);

    connect(m_pointsGenerator, &PointsGenerator::addPoint, this, &MainWindow::addPointToScene);
    connect(m_pointsGenerator, &PointsGenerator::removePoints, this, &MainWindow::removePointsFromScene);
}

MainWindow::~MainWindow()
{
    m_thread.terminate();
    delete ui;

}

void MainWindow::initCustomPlot()
{
    ui->customPlot->clearGraphs();
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->xAxis->setRange(START_RANGE, END_RANGE);
    ui->customPlot->yAxis->setRange(START_RANGE, END_RANGE);
    ui->customPlot->graph(0)->setPen(QPen(POINT_COLOR));//задаем цвет точки
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
    //формируем вид точек
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, POINT_SIZE));
}

void MainWindow::addPointToScene(std::pair<double, double> point)
{
    qDebug("addpointToScene %f, %f", point.first, point.second);
    ui->customPlot->graph(0)->addData(point.first, point.second);
    ui->customPlot->replot();
}

void MainWindow::removePointsFromScene()
{
    qDebug("removePointsFromScene");
    ui->customPlot->removeGraph(0);
    ui->customPlot->replot();
    initCustomPlot();
}
