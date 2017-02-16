#include "serverwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    serverWindow server;
    server.show();

    return a.exec();
}
