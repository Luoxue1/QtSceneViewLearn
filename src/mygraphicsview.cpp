#include "mygraphicsview.h"

#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QMouseEvent>
#include <QPainter>

#include "mygraphicsscene.h"


MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(new MyGraphicsScene(this))
{
    setMouseTracking(true);

    m_scene->setSceneRect(0, 0, 1920, 1080);
    setScene(m_scene);
}

void MyGraphicsView::setCurOpType(OperatorType newCurOpType)
{
    if (m_scene) {
        m_scene->setCurOpType(newCurOpType);
    }
}
