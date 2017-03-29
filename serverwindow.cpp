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

    //create ball
    ball = new Ball(QSize(WIDTH, HEIGHT), 10);

    //create paddle
    int heightPaddle(150), widthPaddle(15);
    leftPaddle = new Paddle(0, 0, widthPaddle, heightPaddle);
    rightPaddle = new Paddle(WIDTH - widthPaddle, 0, widthPaddle, heightPaddle);


    //create limit
    up = new Limit(0, 0, WIDTH, 0);
    down = new Limit(0, HEIGHT, WIDTH, HEIGHT);

    //create scene and add all elements
    scene = new QGraphicsScene();
    scene->addItem(ball);
    scene->addItem(leftPaddle);
    scene->addItem(rightPaddle);
    scene->addItem(up);
    scene->addItem(down);

    //create timer
    timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]{
        QString str("l:" + QString::number(leftPaddle->getPos()) + "/r:" + QString::number(rightPaddle->getPos()) + "/b:" + QString::number(ball->getX()) + ":" + QString::number(ball->getY()));
        std::cout << str.toStdString().c_str() << std::endl;
        this->sendToAll(str);
    });
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
        timer->start(200);
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

    //sendToAll(message);
    sizeMessage = 0;

    QStringList fSplit(message.split(":"));
    if(fSplit.at(0) == "l") {
        leftPaddle->setPosY(fSplit.at(1).toInt());
    } else if(fSplit.at(0) == "r") {
        rightPaddle->setPosY(fSplit.at(1).toInt());
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
