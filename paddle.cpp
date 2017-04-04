#include "paddle.hpp"

Paddle::Paddle(const unsigned int _x, const unsigned int _y, const unsigned _w, const unsigned int _h)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Paddle::setX(const unsigned int pos) {
    x = pos;
}

void Paddle::setY(const unsigned int pos) {
    y = pos;
}

unsigned int Paddle::getX(void) {
    return x;
}

unsigned int Paddle::getY(void) {
    return y;
}

unsigned int Paddle::getWidth(void) {
    return w;
}

unsigned int Paddle::getHeight(void) {
    return h;
}
