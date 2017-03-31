#include "serverwindow.hpp"

#include <iostream>

#include <QThread>

serverWindow::serverWindow()
{
    stateServer = new QLabel("Bug");
    quit = new QPushButton("Quitter");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stateServer);
    layout->addWidget(quit);

    setLayout(layout);
    setWindowTitle("Serveur Ping - Pong");

    connect(quit, SIGNAL(clicked(bool)), qApp, SLOT(quit()));

    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any, 50885)) {
        stateServer->setText("Le serveur n'a pas pu démarrer sur le port " + QString::number(server->serverPort()) + ", raison : "+ server->errorString());
    } else { //if server success to start
        stateServer->setText("Le serveur à bien démarré sur le port " + QString::number(server->serverPort()));
        connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    }

    sizeMessage = 0;

    //create timer
    timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]{
        unsigned int lpy(leftPaddle->getY());
        unsigned int rpy(rightPaddle->getY());
        QString str(QString::number(lpy) + ":" + QString::number(rpy));
        //std::cout << str.toStdString().c_str() << std::endl;
        this->sendToAll(str);
    });

    value = 0;

    leftPaddle = new Paddle(0, 0, 10, 100);
    rightPaddle = new Paddle(this->width() - 10, 0, 10, 100);
}

void serverWindow::newConnection() {
    QTcpSocket *newClient = server->nextPendingConnection();

    if(clients.size() > 2)
        return;

    clients << newClient;

    std::cout << "Nouvelle connection" << std::endl;

    connect(newClient, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(newClient, SIGNAL(disconnected()), this, SLOT(logOutClient()));

    if(clients.size() == 1) {
        this->sendToOne(0, "first");
    } else if(clients.size() == 2) {
        sendToAll("start");
        timer->start(100);
    }

    std::cout << "Taille : " << clients.size() << std::endl;
}

void serverWindow::logOutClient() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    if(socket == 0) //if we don't find client
        return;


    clients.removeOne(socket);
    socket->deleteLater();

    std::cout << "Bye" << std::endl;
}

void serverWindow::receiveData() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    if(socket == 0) //if no client has been found
        return;

    QDataStream in(socket); //stream to read received data

    if(sizeMessage == 0) { //if we don't know the size of message
        if(socket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> sizeMessage;
    }

    QString message;
    in >> message;

    //std::cout << "Message recu : " << message.toStdString().c_str() << std::endl;

    //sendToAll(message);
    sizeMessage = 0;

    QStringList fSPlit(message.split(":"));
    qDebug() << fSPlit.at(0) << fSPlit.at(1);
    if(fSPlit.at(0) == "l") {
        QString ypos(fSPlit.at(1));
        leftPaddle->setY(ypos.toUInt());
    } else if(fSPlit.at(0) == "r") {
        QString ypos(fSPlit.at(1));
        rightPaddle->setY(ypos.toUInt());
    }
}

void serverWindow::sendToAll(const QString &message) {
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message


    for(int i(0) ; i < clients.size() ; i++) {
        clients[i]->write(paquet);
    }
}

void serverWindow::sendToOne(const int player, const QString &message)
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message


    clients[player]->write(paquet);
}
