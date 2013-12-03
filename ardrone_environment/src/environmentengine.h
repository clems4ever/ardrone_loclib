#ifndef ENVIRONMENTENGINE_H
#define ENVIRONMENTENGINE_H

#include <QObject>

class Map2D;

class EnvironmentEngine : public QObject
{
    Q_OBJECT
public:
    EnvironmentEngine(QObject *parent = 0);

    void start();

signals:

public slots:

private:
    Map2D *p_map;

};

#endif // ENVIRONMENTENGINE_H
