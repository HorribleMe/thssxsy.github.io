#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ogdf/basic/Graph_d.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include "topicgraph.h"
#include "paperconferenceauthorgraph.h"
#include <iostream>

using namespace ogdf;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isPgraph = true;
    this->resize(QSize(1000, 800));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionTopicGraph_triggered()
{
    tpoint = new Tgraphwidget(this);
    tpoint->show();
    setCentralWidget(tpoint);
}

void MainWindow::on_actionPCA_Graph_triggered()
{
    ppoint = new Pgraphwidget(this);
    ppoint->show();
    setCentralWidget(ppoint);
}
