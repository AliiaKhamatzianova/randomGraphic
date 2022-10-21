#include "pointsgenerator.h"
#include <QRandomGenerator>
#include <QThread>

PointsGenerator::PointsGenerator()
    :QObject()
{
qRegisterMetaType<std::pair<double, double>>("std::pair<double, double>");
}

void PointsGenerator::startGenerate()
{
    qDebug("startGenerate");
    m_startGenerate = true;

    while(m_startGenerate){
        auto x = QRandomGenerator::global()->bounded(270.f);
        auto y = QRandomGenerator::global()->bounded(270.f);
        m_coords.push_back(std::make_pair(x,y));
        emit addPoint(m_coords.back());
        QThread::currentThread()->msleep(1000);
    }
}

void PointsGenerator::pauseGenerate()
{
    qDebug("pauseGenerate");
    m_startGenerate = false;
}

void PointsGenerator::stopGenerate()
{
    qDebug("stopGenerate");
    m_startGenerate = false;
    m_coords.clear();
    emit removePoints();
}
