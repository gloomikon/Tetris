#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <QWidget>

class Drawable
{
public:
    virtual void draw(QWidget *w) = 0;
    virtual ~Drawable() = 0;
};

#endif // DRAWABLE_H
