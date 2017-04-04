#ifndef PADDLE_HPP
#define PADDLE_HPP


class Paddle
{
public:
    Paddle(const unsigned int _x, const unsigned int _y, const unsigned int _w, const unsigned int _h);
    void setY(const unsigned int pos);
    void setX(const unsigned int pos);
    unsigned int getX(void);
    unsigned int getY(void);
    unsigned int getWidth(void);
    unsigned int getHeight(void);

private:
    unsigned int x, y, w, h;
};

#endif // PADDLE_HPP
