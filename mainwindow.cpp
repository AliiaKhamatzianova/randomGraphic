#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(ui->graphicsView);
    initScene();

    m_pointsGenerator = new PointsGenerator();
    m_pointsGenerator->moveToThread(&m_thread);
    m_thread.start();
    connect(ui->startBtn, &QToolButton::clicked, m_pointsGenerator, &PointsGenerator::startGenerate);
    connect(ui->pauseBtn, &QToolButton::clicked, m_pointsGenerator, &PointsGenerator::pauseGenerate, Qt::ConnectionType::DirectConnection);
    connect(ui->stopBtn, &QToolButton::clicked, m_pointsGenerator, &PointsGenerator::stopGenerate, Qt::ConnectionType::DirectConnection);

    connect(m_pointsGenerator, &PointsGenerator::addPoint, this, &MainWindow::addPointToScene);
    connect(m_pointsGenerator, &PointsGenerator::removePoints, this, &MainWindow::removePointsFromScene);

    ui->graphicsView->setScene(m_scene);
}

MainWindow::~MainWindow()
{
    m_thread.terminate();
    delete ui;

}

void MainWindow::initScene()
{
    QPen pen(Qt::black);
    m_scene->addLine(0,270,270,270,pen);//x
    m_scene->addLine(0,0,0,270,pen);//y
}

void MainWindow::addPointToScene(std::pair<double, double> point)
{
    qDebug("addpointToScene %f, %f", point.first, point.second);
    double rad = 1;
    QPen pen(Qt::blue);
    m_scene->addEllipse(point.first-rad, point.second-rad, rad*2.0, rad*2.0,
                        pen, QBrush(Qt::SolidPattern));
}

void MainWindow::removePointsFromScene()
{
    qDebug("removePointsFromScene");
    m_scene->clear();
    initScene();
}
