#include "mygraphicsscene.h"

#include <QGraphicsItem>
#include <QDebug>

MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    connect(this, &QGraphicsScene::focusItemChanged, this, &MyGraphicsScene::onFocusItemChanged);
    connect(this, &QGraphicsScene::selectionChanged, this, &MyGraphicsScene::onSelectionChanged);
}

OperatorHelper::OperatorType MyGraphicsScene::curOpType() const
{
    return m_curOpType;
}

void MyGraphicsScene::setCurOpType(OperatorType newCurOpType)
{
    qDebug() << __FUNCTION__ << m_curOpType << newCurOpType;
    m_curOpType = newCurOpType;
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    auto *op = m_operatorHelper.findOperator(m_curOpType);
    if (op) {
        op->mouseMoveEvent(mouseEvent, this);
    }
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    auto *op = m_operatorHelper.findOperator(m_curOpType);
    if (op) {
        op->mousePressEvent(mouseEvent, this);
    }
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    auto *op = m_operatorHelper.findOperator(m_curOpType);
    if (op) {
        op->mouseReleaseEvent(mouseEvent, this);
    }
}

void MyGraphicsScene::onSelectionChanged()
{
    qDebug() << __FUNCTION__ << selectedItems();
}

void MyGraphicsScene::onFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason)
{
    qDebug() << __FUNCTION__ << newFocusItem << oldFocusItem << reason;
}
