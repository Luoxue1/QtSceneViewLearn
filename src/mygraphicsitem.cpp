#include "mygraphicsitem.h"

void MyGraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << rect() << pos();

    QGraphicsRectItem::paint(painter, option, widget);
}
