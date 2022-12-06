#include "player.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Multimedia Player");
    QCoreApplication::setOrganizationName("KNU");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    Player player;

    player.show();
    return app.exec();
}
