#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

#include "operatorhelper.h"

class MyGraphicsScene;
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    using OperatorType = OperatorHelper::OperatorType;

    explicit MyGraphicsView(QWidget *parent = nullptr);

    void setCurOpType(OperatorType newCurOpType);

private:
    MyGraphicsScene *m_scene { nullptr };
};

#endif // MYGRAPHICSVIEW_H
