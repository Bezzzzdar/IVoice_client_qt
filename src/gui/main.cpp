#include "mainwindow.h"
#include "core.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto* settings = LibCore::Settings::instance();
    QString serverAddress = settings->getSetting("network/server").toString();
    int serverPort = settings->getSetting("network/port").toInt();

    auto* server = LibCore::Server::instance(serverAddress, serverPort);

    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
