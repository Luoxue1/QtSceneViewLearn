#include "mygraphicsitem.h"

MyGraphicsItem::MyGraphicsItem()
{

}

bool MyGraphicsItem::operatorToolsVisible() const
{
    return m_operatorToolsVisible;
}

void MyGraphicsItem::setOperatorToolsVisible(bool newOperatorToolsVisible)
{
    m_operatorToolsVisible = newOperatorToolsVisible;
    update();
}

QRectF MyGraphicsRectItem::boundingRect() const
{
    return QRectF();
}
