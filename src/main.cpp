#include "include/widgets.h"
#include "include/core.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto* settings = LibCore::Settings::instance();
    QString server_address = settings->getSetting("network/server").toString();
    int server_port = settings->getSetting("network/port").toInt();

    auto* server = LibCore::Server::instance(server_address, server_port);

    MainWindow main_window;

    main_window.show();
    return app.exec();
}
