#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>

#include "operatorhelper.h"

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    using OperatorType = OperatorHelper::OperatorType;
    explicit MyGraphicsScene(QObject *parent = nullptr);

    OperatorType curOpType() const;
    void setCurOpType(OperatorType newCurOpType);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    void onSelectionChanged();
    void onFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason);

    OperatorType m_curOpType { OperatorType::None };
    OperatorHelper m_operatorHelper;
};

#endif // MYGRAPHICSSCENE_H
