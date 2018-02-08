#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "albummodel.h"
#include "picturemodel.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    AlbumModel albumModel;
    PictureModel pictureModel(albumModel);

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("albumModel", &albumModel);
    context->setContextProperty("pictureModel", &pictureModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
