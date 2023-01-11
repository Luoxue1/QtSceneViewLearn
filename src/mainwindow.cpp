#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mygraphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_drawRect = new QAction("drawRect", this);
    connect(m_drawRect, &QAction::triggered, this, &MainWindow::drawRect);
    menuBar()->addAction(m_drawRect);

    m_drawPolygon = new QAction("drawPolygon", this);
    connect(m_drawPolygon, &QAction::triggered, this, &MainWindow::drawPolygon);
    menuBar()->addAction(m_drawPolygon);

    m_drawTriangle = new QAction("drawTriangle", this);
    connect(m_drawTriangle, &QAction::triggered, this, &MainWindow::drawTriangle);
    menuBar()->addAction(m_drawTriangle);

    menuBar()->addSeparator();
    m_deleteItem = new QAction("delete", this);
    connect(m_deleteItem, &QAction::triggered, this, &MainWindow::deleteItem);
    menuBar()->addAction(m_deleteItem);

    m_sceneView = new MyGraphicsView(this);
    setCentralWidget(m_sceneView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawRect()
{
    m_sceneView->setCurOpType(MyGraphicsView::OperatorType::DrawRect);
}

void MainWindow::drawPolygon()
{
    m_sceneView->setCurOpType(MyGraphicsView::OperatorType::DrawPolygon);
}

void MainWindow::drawTriangle()
{

}

void MainWindow::deleteItem()
{

}

