
#include <QCoreApplication>

#include "environmentengine.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    EnvironmentEngine engine;

    engine.start();

    return app.exec();
}
