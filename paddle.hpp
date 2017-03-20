#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QBrush>
#include <QSize>

class Paddle : public QGraphicsRectItem {
public:
    Paddle(int x, int y, int w, int h);

    void setPosY(uint pos);
    int getPos();

private:
    bool yourPaddle;
    int height, width;

    QSize sizeView;

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // PADDLE_HPP
