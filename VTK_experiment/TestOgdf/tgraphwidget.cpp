#include "tgraphwidget.h"
#include "ui_tgraphwidget.h"
#include "topicgraph.h"
#include <QPainter>
#include <QMouseEvent>

Tgraphwidget::Tgraphwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tgraphwidget)
{
    ui->setupUi(this);
    t.createTgraph();
    t.optimizate();
    layoutNum = 0;
    small = false;
    big = false;
    up = down = left = right = false;
    updown = 0;
    leftRight = 0;
    changeRate = 1;
    ui->horizontalSlider->setMinimum(3);
    ui->horizontalSlider->setMaximum(15);
    ui->horizontalSlider->setValue(3);
    ui->horizontalSlider_2->setMinimum(1);
    ui->horizontalSlider_2->setMaximum(6);
    ui->horizontalSlider_2->setValue(2);
}

Tgraphwidget::~Tgraphwidget()
{
    delete ui;
}

void Tgraphwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Graph G;
    GraphAttributes GA(G);
    for (int i = 0; i < 200; i++)
    {
        m_nodes[i] = G.newNode();
    }
    for(int i = 0; i < t.edgeNumber; i++)
    {
        G.newEdge(m_nodes[t.m_edges[i].m_NodeID1], m_nodes[t.m_edges[i].m_NodeID2]);
    }
    FMMMLayout fmmm;
    CircularLayout ball;
    BalloonLayout balloon;
    TutteLayout tutt;
    ModularMultilevelMixer modu;
    if(layoutNum == 0)
    {
        fmmm.call(GA);
    }
    else if(layoutNum == 1)
    {
        ball.call(GA);
    }
    else if(layoutNum == 2)
    {
        balloon.call(GA);
    }
    else if(layoutNum == 3)
    {
        tutt.call(GA);
    }
    else if(layoutNum == 4)
    {
        modu.call(GA);
    }
    painter.setPen(QPen(Qt::red, pointWid));
    painter.setBrush(Qt::red);
    if(small == true)
    {
        changeSize(&GA);
        small = false;
    }
    else if(big == true)
    {
        changeSize(&GA);
        big = false;
    }
    if(up == true)
    {
        changeSize(&GA);
        up = false;
    }
    else if(down == true)
    {
       changeSize(&GA);
        down = false;
    }
    if(left == true)
    {
        changeSize(&GA);
        left = false;
    }
    else if(right == true)
    {
        changeSize(&GA);
        right = false;
    }
    getPoisition(&GA);
    for(int i = 0; i < 200;i++)
    {
        painter.drawEllipse(GA.x(m_nodes[i]) , GA.y(m_nodes[i]), pointWid, pointWid);
    }
    painter.setPen(QPen(Qt::black, (edgeWid / 2.0)));
    for(int i = 0;i < t.edgeNumber;i++)
    {
        painter.drawLine(GA.x(m_nodes[t.m_edges[i].m_NodeID1]), GA.y(m_nodes[t.m_edges[i].m_NodeID1]),
                GA.x(m_nodes[t.m_edges[i].m_NodeID2]), GA.y(m_nodes[t.m_edges[i].m_NodeID2]));
    }
}

void Tgraphwidget::on_pushButton_clicked()
{
    layoutNum = 0;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Tgraphwidget::on_pushButton_2_clicked()
{
    layoutNum = 1;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Tgraphwidget::on_pushButton_3_clicked()
{
    layoutNum = 2;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Tgraphwidget::on_pushButton_5_clicked()
{
    layoutNum = 3;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;

    update();
}

void Tgraphwidget::on_pushButton_6_clicked()
{
    layoutNum = 4;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Tgraphwidget::changeSize(GraphAttributes *GA)
{
    for(int i = 0;i < 200;i++)
    {
        GA->x(m_nodes[i]) *= changeRate;
        GA->y(m_nodes[i]) *= changeRate;
    }
    for(int j = 0;j < 200;j++)
    {
        GA->y(m_nodes[j]) += updown;
    }
    for(int j= 0;j < 200;j++)
    {
        GA->x(m_nodes[j]) += leftRight;
    }
}

void Tgraphwidget::on_pushButton_8_clicked()
{
    small = true;
    changeRate -= 0.02;
    update();
}

void Tgraphwidget::on_pushButton_7_clicked()
{
    big = true;
    changeRate += 0.02;
    update();
}

void Tgraphwidget::getPoisition(GraphAttributes *GA)
{
    for(int i = 0;i < 200;i++)
    {
        for(int j = 0;j < 2;j++)
        {
            if(j == 0)
                poisition[i][j] = GA->x(m_nodes[i]);
            else
                poisition[i][j] = GA->y(m_nodes[i]);
        }
    }
}

void Tgraphwidget::mousePressEvent(QMouseEvent *event)
{
    bool find = false;
    if(event->button() == Qt::LeftButton)
    {
        for(int i = 0;i < 200;i++)
        {
            if(event->pos().x() <= (poisition[i][0] + 5) && event->pos().x() >= (poisition[i][0] - 5))
            {
                if(event->pos().y() <= (poisition[i][1] + 5) && event->pos().y() >= (poisition[i][1] - 5))
                {
                    showContent(i);
                    find = true;
                    break;
                }
            }
        }
        if(find == false)
            ui->textEdit->setText("node not found");
    }
}

void Tgraphwidget::showContent(int i)
{
    string tem1;
    tem1 = t.m_nodes[i].m_DocumentID + "\r" + t.m_nodes[i].m_TopicWords;
    QString tem2 = QString(QString::fromLocal8Bit(tem1.c_str()));
    ui->textEdit->setText(tem2);
}

void Tgraphwidget::on_pushButton_9_clicked()
{
    up = true;
    updown -= 20;
    update();
}

void Tgraphwidget::on_pushButton_12_clicked()
{
    down = true;
    updown += 20;
    update();
}

void Tgraphwidget::on_pushButton_11_clicked()
{
    left = true;
    leftRight -= 20;
    update();
}

void Tgraphwidget::on_pushButton_10_clicked()
{
    right = true;
    leftRight += 20;
    update();
}

void Tgraphwidget::on_horizontalSlider_valueChanged(int value)
{
    pointWid = value;
}

void Tgraphwidget::on_horizontalSlider_2_valueChanged(int value)
{
    edgeWid = value;
}

void Tgraphwidget::on_pushButton_13_clicked()
{
    QPixmap x = QPixmap::grabWidget(this);
    x.save("/Users/THSS-XSY/Documents/QtProjects/TestOgdf/save/Tgraph.png","png" );
}
