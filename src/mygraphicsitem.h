#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsItem>

class MyGraphicsItem : public QGraphicsItem
{
public:
    MyGraphicsItem();

    bool operatorToolsVisible() const;
    void setOperatorToolsVisible(bool newOperatorToolsVisible);

private:
    bool m_operatorToolsVisible { false };
};

class MyGraphicsRectItem : public MyGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QRectF m_rectContent;
};

#endif // MYGRAPHICSITEM_H
