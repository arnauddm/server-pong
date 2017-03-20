#include "ball.hpp"

Ball::Ball(const QSize _window, const int _size) {
    sizeView = _window;

    //create ball
    setRect(0, 0, _size, _size);
    size = _size;
    setX(sizeView.width() / 2);
    setY(sizeView.height() / 2);

    //connect timer to function move
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(move()));

    //start timer
    timer->start(10);

    //init direction
    //moveX = (qrand() % 2) - 1;
    //moveY = (qrand() % 2) - 1;

    moveX = -1;
    moveY = 1;

    //change color
    this->setBrush(Qt::black);
}

void Ball::reset()
{
    this->setPos(this->sizeView.width() / 2, this->sizeView.height() / 2);

}

void Ball::move() {
    this->setPos(this->x() + 2 * moveX, this->y() + 2 * moveY);

    //detect collide with item
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for(int i(0) ; i < colliding_item.size() ; i++) {
        if(typeid(*(colliding_item[i])) == typeid(Paddle)) {
            this->moveX *= -1;
        } else if(typeid(*(colliding_item[i])) == typeid(Limit)) {
            this->moveY *= -1;
        }
    }

    if(this->pos().x() < 0 || this->pos().x() > this->sizeView.width())
        this->reset();
}

int Ball::getX() {
    return this->x();
}

int Ball::getY() {
    return this->y();
}
