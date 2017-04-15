#include <cstdlib>
#include <array>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFile>

#include "notification/notificationmanager.h"

const QString home_path = QString(std::getenv("HOME"));
const std::array<QString, 2> search_paths = {
    home_path + QString("/.config/qmlnotify/"), // Home directory
    QString("/etc/qmlnotify/") // Global configuration directory
};

// Return the path of the component.
// Returns "" if the component is not in the search paths.
QString get_component_path(QString component) {
    for (unsigned int i = 0; i < search_paths.size(); i++) {
        // qDebug() << "Checking" << search_paths[i];
        // qDebug() << search_paths[i] + component;
	if (QFile::exists(search_paths[i] + component)) {
	    return search_paths[i] + component;
	}
    }

    // No match found
    return QString("");
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QGuiApplication::setQuitOnLastWindowClosed(false);

    //Use reference implementation as default notification
    QString component_path = "qrc:/Default.qml";

    for (int i = 0; i < argc; i++) {
        if (QString(argv[i]) == "--qml") {
            if (++i < argc) {
                component_path = get_component_path(QString(argv[i]).trimmed());
		
		// Tell the user that we were not able to find the component
		if (component_path == "") {
           	    qDebug() << "Error: Could not find" << QString(argv[i]).trimmed() << "in the search paths";
		    return 1;
		} 
	    }
        }
    }

    QQmlApplicationEngine engine;

    QObject obj;
    NotificationManager *mgr = new NotificationManager(&engine, component_path, &obj);
    Q_UNUSED(mgr);

    return app.exec();
}
