#include "filteredrostermodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<RosterListModel>("App", 1, 0, "RosterListModel");
    qmlRegisterType<FilteredRosterModel>("App", 1, 0, "FilteredRosterModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine,
                     &QQmlApplicationEngine::objectCreated,
                     &app,
                     [url](QObject* obj, const QUrl& objUrl)
                     {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

