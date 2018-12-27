#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <QWidget>

class Drawable
{
public:
    virtual void draw(QWidget *w);
    virtual ~Drawable() = 0;
};

#endif // DRAWABLE_H
