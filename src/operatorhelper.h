#ifndef OPERATORHELPER_H
#define OPERATORHELPER_H

#include <QPointF>
#include <QHash>
#include <QPolygonF>

class QGraphicsSceneMouseEvent;
class QGraphicsRectItem;
class QGraphicsPolygonItem;
class MyGraphicsScene;
class OperatorBase;

class OperatorHelper
{
public:
    enum OperatorType {
        None,
        // draw
        DrawRect,
        DrawTriangle,
        DrawPolygon,
        // item
        Select,
        MoveItem,
        ResizeItem
    };

    OperatorHelper();

    OperatorBase *findOperator(OperatorType type) const;

private:
    QHash<OperatorType, OperatorBase*> m_operators;
};

class OperatorBase {
public:
    using OpType = OperatorHelper::OperatorType;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene);

    OpType m_opType { OpType::None };
    QPointF m_pressPos;
    QPointF m_latestPos;
};

class DrawRectOperator: public OperatorBase {
public:
    explicit DrawRectOperator()
    {
        m_opType = OpType::DrawRect;
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;

private:
    QGraphicsRectItem *m_rectItem { nullptr };
};

class DrawPolygonOperator: public OperatorBase {
public:
    explicit DrawPolygonOperator()
    {
        m_opType = OpType::DrawPolygon;
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;

private:
    QGraphicsPolygonItem *m_polygonItem { nullptr };
    QPolygonF m_polygonTemp;
};

class QGraphicsItem;
class SelectOperator: public OperatorBase
{
public:
    SelectOperator()
    {
        m_opType = OpType::Select;
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene) override;

private:
    bool m_pressed { false };
    QHash<QGraphicsItem *, QPointF> m_initialPositions;
};


#endif // OPERATORHELPER_H
