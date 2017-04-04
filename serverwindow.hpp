#ifndef SERVERWINDOW_HPP
#define SERVERWINDOW_HPP

#include "paddle.hpp"
#include "ball.hpp"

#include <QtWidgets>
#include <QtNetwork>
#include <QTimer>
#include <QGraphicsScene>

#define WIDTH 1000
#define HEIGHT 640

class serverWindow : public QWidget
{
    Q_OBJECT
public:
    serverWindow();

    void sendToAll(const QString &message);
    void sendToOne(const int player, const QString &message);

private:
    QLabel *stateServer;
    QPushButton *quit;

    QTcpServer *server;
    QList<QTcpSocket *> clients;
    quint16 sizeMessage;

    QTimer *timer;

    Paddle *leftPaddle;
    Paddle *rightPaddle;
    Ball *ball;

    int value;

signals:

private slots:
    void newConnection();
    void receiveData();
    void logOutClient();
    void updateAndSendPosition();
};

#endif // SERVERWINDOW_HPP
