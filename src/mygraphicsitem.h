#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsItem>

class MyGraphicsRectItem : public QGraphicsRectItem
{
public:
    MyGraphicsRectItem() = default;
    ~MyGraphicsRectItem() = default;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // MYGRAPHICSITEM_H
