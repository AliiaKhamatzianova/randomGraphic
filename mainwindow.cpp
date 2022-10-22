#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

#include "Defines.h"


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
    QPen pen(AXES_COLOR);
    m_scene->addLine(0,MAX_POINT,MAX_POINT,MAX_POINT,pen); //x
    m_scene->addLine(0,0,0,MAX_POINT,pen); //y
}

void MainWindow::addPointToScene(std::pair<double, double> point)
{
    qDebug("addpointToScene %f, %f", point.first, point.second);
    QPen pen(POINT_COLOR);
    m_scene->addEllipse(point.first-RAD, point.second-RAD, RAD*2.0, RAD*2.0,
                        pen, QBrush(POINT_BRUSH_STYLE));
}

void MainWindow::removePointsFromScene()
{
    qDebug("removePointsFromScene");
    m_scene->clear();
    initScene();
}
