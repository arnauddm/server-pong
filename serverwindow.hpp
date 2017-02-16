#ifndef SERVERWINDOW_HPP
#define SERVERWINDOW_HPP

#include <QtWidgets>
#include <QtNetwork>

class serverWindow : public QWidget
{
    Q_OBJECT
public:
    serverWindow();

public slots:
    void sendToAll(const QString &message);
    void sendToOne(const int player, const QString &message);

private:
    QLabel *stateServer;
    QPushButton *quit;

    QTcpServer *server;
    QList<QTcpSocket *> clients;
    quint16 sizeMessage;

signals:

public slots:

private slots:
    void newConnection();
    void receiveData();
    void logOutClient();
};

#endif // SERVERWINDOW_HPP
