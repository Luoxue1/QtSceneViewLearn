#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MyGraphicsView;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void drawRect();
    void drawPolygon();
    void drawTriangle();
    void deleteItem();

    Ui::MainWindow *ui;
    QAction *m_drawRect { nullptr };
    QAction *m_drawPolygon { nullptr };
    QAction *m_drawTriangle { nullptr };
    QAction *m_deleteItem { nullptr };
    MyGraphicsView *m_sceneView { nullptr };
};
#endif // MAINWINDOW_H
