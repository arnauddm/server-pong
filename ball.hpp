#ifndef BALL_HPP
#define BALL_HPP

#include "paddle.hpp"
#include "limit.hpp"

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QGraphicsView>
#include <QBrush>
#include <QList>
#include <QSize>

class Ball : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    Ball(const QSize _window, const int _size);

    void reset();
    int getX();
    int getY();

private:
    int moveX, moveY, size;
    QSize sizeView;

signals:

private slots:
    void move();
};

#endif // BALL_HPP
