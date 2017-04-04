#ifndef BALL_HPP
#define BALL_HPP

#include <QSize>

#include <QtMath>
#include <qmath.h>
#include <QtGlobal>

class Ball
{
public:
    Ball(const unsigned int _w, const unsigned int _h);

    void move();
    void restart();
    void reverseX();
    void reverseY();

    void setX(const unsigned int pos);
    void setY(const unsigned int pos);
    void setHeight(const unsigned int value);
    void setWidth(const unsigned int value);

    unsigned int getX();
    unsigned int getY();
    unsigned int getHeight();
    unsigned int getWidth();

private:
    int x, y, width, height;
    int dx, dy;
    QSize window;

};

#endif // BALL_HPP
