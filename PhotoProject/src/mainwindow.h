#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QPainter>
#include "opencv2/opencv.hpp"
#include "dialog.h"
#define PI       3.14159

enum CaptureState{
    initCapture,
    beginCaptureImage,
    finishCaptureImage,
    beginMoveCaptureArea,
    finishMoveCaptureArea,
};

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_2_sliderPressed();

    void on_horizontalSlider_2_sliderReleased();

    void on_horizontalSlider_3_sliderPressed();

    void on_horizontalSlider_3_sliderReleased();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void receiveData(QString data);

    void gammaTrans(QString data);

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void histogramMatch(QString path);

    void onedHistSpecify( cv::Mat *src, cv::Mat *dst, cv::Mat *result);

    void on_action_6_triggered();

    void midWave(QString data);

    void on_action_7_triggered();

    void guassWave(QString data);

    void on_action_8_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void smoothWave(QString data);

    void on_action_11_triggered();

    void sharpenWave(QString data);

    void on_action_12_triggered();

    void on_action_13_triggered();

    void on_actionLOMO_triggered();

private:
    Ui::MainWindow *ui;
    void initWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    bool isPressPointInSelectRect(QPoint mousePressPoint);
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
    QRect getMoveRect();
    QPoint getMovePoint();
    QRect getSelectRect();

    QImage cvMatToQimage(const cv::Mat& mat);
    cv::Mat qimageToCvMat(QImage image);
    void getRGB(cv::Mat img);
    void getHSI(cv::Mat img);
    void HSI2RGB();
    void refreshRGB();
    void delete1(int **);
    void delete2(double **);
    void checkAndDelete();
    void circleColorful();
    void getMean();
    void myEqualizeHist(CvArr* srcarr, CvArr* dstarr);
    //IplImage* myDrawHistogram(int )

private:
    bool working;
    double alpha;
    int **R, **G, **B;
    double **H, **S, **I;
    double **_H, **_S, **_I;
    unsigned long long red, green, blue;
    int beta;
    cv::Mat image;
    cv::Mat temColorImage;
    QPixmap m_loadPixmap, m_capturePixmap;
    int m_screenwidth;
    int m_screenheight;
    QPoint m_beginPoint, m_endPoint , m_beginMovePoint , m_endMovePoint;
    CaptureState m_currentCaptureState;
    QRect m_currentSelectRect;
    int p[256];
    int dst_p[256];
};

#endif // MAINWINDOW_H
