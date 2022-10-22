#ifndef POINTSGENERATOR_H
#define POINTSGENERATOR_H

#include <QObject>
#include <atomic>
#include <QMetaType>

class PointsGenerator: public QObject
{
    Q_OBJECT
public:
    PointsGenerator();
    ~PointsGenerator();


    void startGenerate();
    void pauseGenerate();
    void stopGenerate();

signals:
    void addPoint(std::pair<double, double>);
    void removePoints();

private:
    std::vector<std::pair<double, double>> m_coords;
    std::atomic_bool m_startGenerate = false;

};

#endif // POINTSGENERATOR_H
