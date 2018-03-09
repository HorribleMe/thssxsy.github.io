#include "pgraphwidget.h"
#include "ui_pgraphwidget.h"
#include <QPainter>
#include "paperconferenceauthorgraph.h"
#include <QMouseEvent>
#include <QApplication>

using namespace ogdf;

Pgraphwidget::Pgraphwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pgraphwidget)
{
    ui->setupUi(this);
    p.createPgraph();
    p.optimizate();
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


Pgraphwidget::~Pgraphwidget()
{
    delete ui;
}

void Pgraphwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Graph G;
    GraphAttributes GA(G);
    for (int i = 0; i < 200; i++)
    {
        m_nodes[i] = G.newNode();
    }
    for(int i = 0; i < p.edgeNumber; i++)
    {
        G.newEdge(m_nodes[p.m_edge[i].m_node1], m_nodes[p.m_edge[i].m_node2]);
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
        if(i > p.pnumber)
        {
            painter.setPen(QPen(Qt::yellow, pointWid));
            painter.setBrush(Qt::yellow);
        }
        if(i > p.pnumber + p.cnumber)
        {
            painter.setPen(QPen(Qt::blue, pointWid));
            painter.setBrush(Qt::blue);
        }
        painter.drawEllipse(GA.x(m_nodes[i]), GA.y(m_nodes[i]), pointWid, pointWid);
    }
    painter.setPen(QPen(Qt::black, (edgeWid / 2.0)));
    for(int i = 0;i < p.edgeNumber;i++)
    {
        painter.drawLine(GA.x(m_nodes[p.m_edge[i].m_node1]), GA.y(m_nodes[p.m_edge[i].m_node1]),
                GA.x(m_nodes[p.m_edge[i].m_node2]), GA.y(m_nodes[p.m_edge[i].m_node2]));
    }
}

void Pgraphwidget::on_pushButton_clicked()
{
    layoutNum = 0;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Pgraphwidget::on_pushButton_2_clicked()
{
    layoutNum = 1;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Pgraphwidget::on_pushButton_3_clicked()
{
    layoutNum = 2;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Pgraphwidget::on_pushButton_6_clicked()
{
    layoutNum = 3;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Pgraphwidget::on_pushButton_7_clicked()
{
    layoutNum = 4;
    changeRate = 1.0;
    updown = 0;
    leftRight = 0;
    update();
}

void Pgraphwidget::changeSize(GraphAttributes *GA)
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

void Pgraphwidget::on_pushButton_4_clicked()
{
    small = true;
    changeRate -= 0.02;
    update();
}


void Pgraphwidget::on_pushButton_5_clicked()
{
    big = true;
    changeRate += 0.02;
    update();
}

void Pgraphwidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        for(int i = 0;i < 200;i++)
        {
            if(event->pos().x() <= (poisition[i][0] + 5) && event->pos().x() >= (poisition[i][0] - 5))
            {
                if(event->pos().y() <= (poisition[i][1] + 5) && event->pos().y() >= (poisition[i][1] - 5))
                {
                    showContent(i);
                    break;
                }
                else
                    ui->textEdit->setText("node not found");
            }
            else
                ui->textEdit->setText("node not found");
        }
    }
}

void Pgraphwidget::getPoisition(GraphAttributes *GA)
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

void Pgraphwidget::showContent(int i)
{
    if(i <= p.pnumber)
    {
        string tem1;
        tem1 = "ID:" + p.m_pnode[i].m_ID +"type:"+ p.m_pnode[i].m_type +
                "\rAuthor:" + p.m_pnode[i].m_author + "paperTitle:" + p.m_pnode[i].m_paperTitle;
        QString tem2 = QString(QString::fromLocal8Bit(tem1.c_str()));
        ui->textEdit->setText(tem2);
    }
    else
    {
        i -= p.pnumber;
        if(i <= p.cnumber)
        {
            string tem1;
            tem1 = "ID:" + p.m_cnode[i].m_ID +"type:"+ p.m_cnode[i].m_type +
                    "\rconferenceName:" + p.m_cnode[i].m_conferenceName + "shortName:" +
                    p.m_cnode[i].m_shortName;
            QString tem2 = QString(QString::fromLocal8Bit(tem1.c_str()));
            ui->textEdit->setText(tem2);
        }
        else
        {
          i -= p.cnumber;
          if(i <= p.anumber)
          {
              string tem1;
              tem1 = "ID:" + p.m_anode[i].m_ID +"type:"+ p.m_anode[i].m_type +
                      "\rAuthorName:" + p.m_anode[i].m_authorName + "shortName:" + p.m_anode[i].m_shortAuthorName;
              QString tem2 = QString(QString::fromLocal8Bit(tem1.c_str()));
              ui->textEdit->setText(tem2);
          }
        }
    }
}

void Pgraphwidget::on_pushButton_9_clicked()
{
    up = true;
    updown -= 20;
    update();
}

void Pgraphwidget::on_pushButton_12_clicked()
{
    down =true;
    updown += 20;
    update();
}

void Pgraphwidget::on_pushButton_10_clicked()
{
    left = true;
    leftRight -= 20;
    update();
}

void Pgraphwidget::on_pushButton_11_clicked()
{
    right = true;
    leftRight += 20;
    update();
}

void Pgraphwidget::on_horizontalSlider_valueChanged(int value)
{
    pointWid = value;
}

void Pgraphwidget::on_horizontalSlider_2_valueChanged(int value)
{
    edgeWid = value;
}

void Pgraphwidget::on_pushButton_13_clicked()
{
    savePic();
}

void Pgraphwidget::savePic()
{
    QPixmap x = QPixmap::grabWidget(this);
    x.save("/Users/THSS-XSY/Documents/QtProjects/TestOgdf/save/Pgraph.png","png" );
}
