#include "mainwindow.h"
#include "core.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LibCore::Logger::instance()->setLogFile("logs/app.log");
    LOG(Info) << "Start application\n";

    auto* settings = LibCore::Settings::instance();
    LOG(Info) << "Init settings\n";
    const QString serverAddress = settings->getSetting("network/server").toString();
    const int serverPort = settings->getSetting("network/port").toInt();

    auto* server = LibCore::Server::instance(serverAddress, serverPort);
    LOG(Info) << "Run server\n";

    auto* user = LibCore::User::instance();
    LOG(Info) << "Init empty user\n";

    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
