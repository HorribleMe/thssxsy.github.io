#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ogdf/basic/Graph_d.h>
#include "tgraphwidget.h"
#include "pgraphwidget.h"

using namespace ogdf;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionTopicGraph_triggered();

    void on_actionPCA_Graph_triggered();

private:
    Ui::MainWindow *ui;
    bool isPgraph;
    Tgraphwidget *tpoint;
    Pgraphwidget *ppoint;
};

#endif // MAINWINDOW_H
