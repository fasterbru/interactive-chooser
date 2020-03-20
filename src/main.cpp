#include <QGuiApplication>
#include <QDebug>
#include <QObject>

#include <QQmlEngine>


#include "x11_notifier.h"
#include "geometry_updater.h"

#include "model_factory.h"
#include "main_window.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    Model_factory factory(argc, argv);
    auto model = factory.create();

    if (!model) {
        qCritical() << "Couldn't create model";
        exit(-1);
    }

    QQmlEngine engine;

    Main_window main_window(engine, *model);
    auto window = main_window.quick_window();

    if (!window) {
        qCritical() << "Couldn't create window";
        exit(-1);
    }

    X11_notifier x11;

    Geometry_updater updater(*window, x11);
    window->show();

    return app.exec();
}
