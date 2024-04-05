#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "BFS_class.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/C_connection/assets/images/linegraphsymbol_120645.ico"));


    QQmlApplicationEngine engine;

    BFS_class* bfs = new BFS_class(5, 5, 3, 10, &app);
    qmlRegisterSingletonInstance("BFS", 1, 0, "BFS", bfs);

    const QUrl url(u"qrc:/C_connection/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();


    return 0;
}
