#ifndef TGRAPHWIDGET_H
#define TGRAPHWIDGET_H

#include <QWidget>
#include "topicgraph.h"
#include <ogdf/basic/Graph_d.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/misclayout/BalloonLayout.h>
#include <ogdf/misclayout/CircularLayout.h>
#include <ogdf/energybased/TutteLayout.h>
#include <ogdf/energybased/multilevelmixer/ModularMultilevelMixer.h>

using namespace ogdf;

namespace Ui {
class Tgraphwidget;
}

class Tgraphwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Tgraphwidget(QWidget *parent = 0);
    ~Tgraphwidget();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_13_clicked();

private:
    Tgraph t;
    Ui::Tgraphwidget *ui;
    int layoutNum;
    node m_nodes[200];
    double poisition[200][2];
    void getPoisition(GraphAttributes *GA);
    void changeSize(GraphAttributes *GA);
    void showContent(int i);
    bool big;
    bool small;
    bool up;
    bool down;
    bool left;
    bool right;
    int updown;
    int leftRight;
    int pointWid;
    int edgeWid;
    double changeRate;
};

#endif // TGRAPHWIDGET_H
