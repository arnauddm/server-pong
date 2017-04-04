#include "ball.hpp"

Ball::Ball(const unsigned int _w, const unsigned int _h)
{
    width = _w;
    height = _h;


    window = QSize(1000, 600);

    //dx = (qrand() % 4) - 2;
    //dy = (qrand() % 4) - 2;
    dx = 1;
    dy = 1;
}

void Ball::move() {
    x += dx;
    y += dy;
}

void Ball::restart() {
    x = window.width() / 2;
    y = window.height() / 2;
}

void Ball::setX(const unsigned int pos) {
    x = pos;
}

void Ball::setY(const unsigned int pos) {
    y = pos;
}

void Ball::setHeight(const unsigned int value) {
    height = value;
}

void Ball::setWidth(const unsigned int value) {
    width = value;
}

unsigned int Ball::getX() {
    return x;
}

unsigned int Ball::getY() {
    return y;
}

unsigned int Ball::getHeight() {
    return height;
}

unsigned int Ball::getWidth() {
    return width;
}

void Ball::reverseX() {
    dx *= -1;
}

void Ball::reverseY() {
    dy *= -1;
}
