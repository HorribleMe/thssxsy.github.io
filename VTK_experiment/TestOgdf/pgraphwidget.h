#ifndef PGRAPHWIDGET_H
#define PGRAPHWIDGET_H

#include <QWidget>
#include <QPixmap>
#include "paperconferenceauthorgraph.h"
#include <ogdf/basic/Graph_d.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/misclayout/BalloonLayout.h>
#include <ogdf/misclayout/CircularLayout.h>
#include <ogdf/energybased/TutteLayout.h>
#include <ogdf/energybased/multilevelmixer/ModularMultilevelMixer.h>

using namespace ogdf;

namespace Ui {
class Pgraphwidget;
}

class Pgraphwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Pgraphwidget(QWidget *parent = 0);
    ~Pgraphwidget();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


    void on_pushButton_5_clicked();


    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();


    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_13_clicked();

private:
    Pgraph p;
    Ui::Pgraphwidget *ui;
    int layoutNum;
    node m_nodes[200];
    double poisition[200][2];
    void getPoisition(GraphAttributes *GA);
    void changeSize(GraphAttributes *GA);
    void savePic();
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

#endif // PGRAPHWIDGET_H
