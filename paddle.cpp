#include "paddle.hpp"

Paddle::Paddle(int x,
               int y,
               int w,
               int h) {
    //create paddle
    this->setRect(x, y, w, h);

    //init var
    this->yourPaddle = yourPaddle;

    this->height = h;
    this->width = w;
    this->sizeView = sizeView;

    //set focusable, "select this on screen" if this is your paddle
    if(this->yourPaddle) {
        this->setFlag(QGraphicsRectItem::ItemIsFocusable);
        this->setFocus();
    }

    //change color
    if(this->yourPaddle)
        this->setBrush(Qt::red);
    else
        this->setBrush(Qt::black);
}

void Paddle::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Up && this->yourPaddle)
        this->setPos(x(), y() - 15);
    else if(event->key() == Qt::Key_Down && this->yourPaddle)
        this->setPos(x(), y() + 15);

    if(this->pos().y() < 0)
        this->setPos(this->pos().x(), 0);

    if(this->pos().y() + this->height > this->sizeView.height())
        this->setPos(this->pos().x(), this->sizeView.height() - this->height);
}

void Paddle::setPosY(uint pos) {
    this->setPos(this->pos().x(), pos);
}

int Paddle::getPos() {
    return this->pos().y();
}
