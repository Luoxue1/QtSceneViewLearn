#include "operatorhelper.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QRectF>
#include <QtMath>

#include "mygraphicsscene.h"

static QColor randomColor()
{
    return QColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
}

OperatorHelper::OperatorHelper()
{
    m_operators.insert(OperatorType::DrawRect, new DrawRectOperator);
    m_operators.insert(OperatorType::DrawPolygon, new DrawPolygonOperator);
    m_operators.insert(OperatorType::Select, new SelectOperator);
}

OperatorBase *OperatorHelper::findOperator(OperatorType type) const
{
    return m_operators.value(type);
}


void OperatorBase::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    Q_UNUSED(scene)
    m_latestPos = mouseEvent->scenePos();
}

void OperatorBase::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    Q_UNUSED(scene)
    m_pressPos = mouseEvent->scenePos();
    m_latestPos = m_pressPos;
}

void OperatorBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    Q_UNUSED(mouseEvent)
    Q_UNUSED(scene)
}

void DrawRectOperator::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    OperatorBase::mouseMoveEvent(mouseEvent, scene);

    if (!m_rectItem) {
        return;
    }

    // caculate rect
    qreal x = qMin(m_pressPos.x(), m_latestPos.x());
    qreal y = qMin(m_pressPos.y(), m_latestPos.y());
    qreal width = qAbs(m_pressPos.x() - m_latestPos.x());
    qreal height = qAbs(m_pressPos.y() - m_latestPos.y());
    m_rectItem->setPos(x, y);
    m_rectItem->setRect(0, 0, width, height);
}

void DrawRectOperator::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    OperatorBase::mousePressEvent(mouseEvent, scene);

    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    scene->clearSelection();
    m_rectItem = new QGraphicsRectItem(m_pressPos.x(), m_pressPos.y(), 1, 1);
    m_rectItem->setPos(m_pressPos);
    m_rectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    m_rectItem->setBrush(randomColor());
    scene->addItem(m_rectItem);
    m_rectItem->setSelected(true);
}

void DrawRectOperator::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    OperatorBase::mouseReleaseEvent(mouseEvent, scene);

    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    scene->setCurOpType(OpType::Select);

    if (!m_rectItem) {
        return;
    }

    if (qFuzzyCompare(1.0, QLineF(m_pressPos, m_latestPos).length()) && m_rectItem) {
        scene->removeItem(m_rectItem);
        delete m_rectItem;
        m_rectItem = nullptr;
    }

    m_rectItem = nullptr;
}

void DrawPolygonOperator::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    OperatorBase::mouseMoveEvent(mouseEvent, scene);

    if (!m_polygonItem) {
        return;
    }

    QPolygonF p(m_polygonTemp);
    p += m_latestPos;
    m_polygonItem->setPolygon(p);
}

void DrawPolygonOperator::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    OperatorBase::mousePressEvent(mouseEvent, scene);

    if (mouseEvent->button() != Qt::LeftButton) {
        // end draw polygon
        if (m_polygonTemp.size() < 2 && m_polygonItem) {
            scene->removeItem(m_polygonItem);
            delete m_polygonItem;
            m_polygonItem = nullptr;
        }

        if (!m_polygonTemp.isClosed() && m_polygonItem) {
            m_polygonTemp.append(m_polygonTemp.first());
            m_polygonItem->setPolygon(m_polygonTemp);
        }

        m_polygonItem = nullptr;
        scene->setCurOpType(OpType::Select);
        m_polygonTemp.clear();
        return;
    }

    scene->clearSelection();

    if (!m_polygonItem) {
        m_polygonTemp.clear();
        m_polygonItem = new QGraphicsPolygonItem;
        m_polygonItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        m_polygonItem->setBrush(randomColor());
        scene->addItem(m_polygonItem);
        m_polygonTemp.append(m_pressPos);
    } else {
        m_polygonTemp += m_pressPos;
        m_polygonItem->setPolygon(m_polygonTemp);
    }
}

void SelectOperator::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    if (!m_pressed || m_initialPositions.isEmpty()) {
        return;
    }

    auto items = scene->items(mouseEvent->scenePos());
    for (auto *item : items) {
        item->setPos(m_initialPositions.value(item) + mouseEvent->scenePos() - m_pressPos);
    }
}

void SelectOperator::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    OperatorBase::mousePressEvent(mouseEvent, scene);
    m_pressed = true;

    m_initialPositions.clear();
    scene->clearSelection();
    auto items = scene->items(mouseEvent->scenePos());
    for (auto *item : items) {
        item->setSelected(true);
        m_initialPositions.insert(item, item->pos());
    }
}

void SelectOperator::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, MyGraphicsScene *scene)
{
    OperatorBase::mouseReleaseEvent(mouseEvent, scene);
    m_pressed = false;
}
