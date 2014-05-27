#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QDebug>
#include <QQmlContext>

#include "backend.h"
#include "soundmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
	QtQuick2ApplicationViewer viewer;

	// Model
	Backend backend(viewer.rootContext());

	// View
	viewer.setMainQmlFile(QStringLiteral("qml/DnDSoundScape/main.qml"));
	viewer.showExpanded();

    return app.exec();
}
