#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"
#include "QFileDialog"
#include "QMessageBox"
#include "QDebug"
#include <QMouseEvent>
#include <QPainter>
#include <QDialog>
#include <vector>
#include <cmath>
#include <algorithm>
#include "dialog.h"
#include <QStringList>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    checkAndDelete();
}

void MainWindow::initWindow()
{
    this->resize(QSize(1200, 800));
    this->setMouseTracking(true);
    H = NULL;
    S = NULL;
    I = NULL;
    R = NULL;
    G = NULL;
    B = NULL;
    _H = NULL;
    _S = NULL;
    _I = NULL;
    working = false;
    m_currentCaptureState = initCapture;
    m_screenwidth = 0;
    m_screenheight = 0;
    m_beginPoint.setX(0);
    m_beginPoint.setY(0);
    m_endPoint.setX(0);
    m_endPoint.setY(0);
    red = 0;
    green = 0;
    blue = 0;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(working == true)
    {
        if(event->button() == Qt::LeftButton && m_currentCaptureState == initCapture)
        {
            m_currentCaptureState = beginCaptureImage;
            m_beginPoint = event->pos();
        }
        else if(event->button() == Qt::LeftButton && m_currentCaptureState == finishCaptureImage)
        {
            if(isPressPointInSelectRect(event->pos()))
            {
                m_currentCaptureState = beginMoveCaptureArea;
                setCursor(Qt::SizeAllCursor);
                m_beginMovePoint = event->pos();
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(m_currentCaptureState == beginCaptureImage)
    {
        m_endPoint = event->pos();
        /*int img_x = ui->label->x();
        int img_y = ui->label->y();

        int x = event->x();
        int y = event->y();
        int max_x = img_x + ui->label->width();
        int max_y = img_y + ui->label->height();
        x = max(x, img_x);
        y = max(y, img_y);
        x = min(x, max_x);
        y = min(y, max_y);
        int _x = min(x, m_beginPoint.x());
        int _y = min(y, m_beginPoint.y());
        _x = _x - img_x;
        _y = _y - img_y;
        QRect select = getSelectRect();
        int width = select.width() + _x;
        int height = select.height() + _y;
        cv::Mat temp;
        image.copyTo(temp);
        for(int i = _x;i <=  width;i++)
        {
            temp.at<Vec3b>(_y, i) = Vec3b(0, 0, 0);
            temp.at<Vec3b>(height, i) = Vec3b(0, 0, 0);
        }
        for(int j = _y;j <=  height;j++)
        {
            temp.at<Vec3b>(j, _x) = Vec3b(0, 0, 0);
            temp.at<Vec3b>(j, width) = Vec3b(0, 0, 0);
        }
        QImage img = cvMatToQimage(temp);
        m_loadPixmap = QPixmap::fromImage(img);
        ui->label->setPixmap(m_loadPixmap);*/
        update();
    }
    else if(m_currentCaptureState == beginMoveCaptureArea)
    {
        m_endMovePoint = event->pos();
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_currentCaptureState == beginCaptureImage)
    {
        m_currentCaptureState = finishCaptureImage;
        setCursor(Qt::ArrowCursor);
        m_endPoint = event->pos();
        update();
    }
    else if(m_currentCaptureState == beginMoveCaptureArea)
    {
        m_currentCaptureState = finishMoveCaptureArea;
        setCursor(Qt::ArrowCursor);
        m_endMovePoint = event->pos();
        update();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        if(m_currentCaptureState == finishCaptureImage || m_currentCaptureState == finishMoveCaptureArea)
        {
            int x, y;
            x = ui->label->x();
            y = ui->label->y();
            QRect temp = getSelectRect();
            cv::Mat newImage;
            newImage = image(cv::Rect(temp.x() - x, temp.y() - y, temp.width(), temp.height()));
            image = newImage;
            QImage img = cvMatToQimage(image);
            m_loadPixmap = QPixmap::fromImage(img);
            ui->label->setPixmap(m_loadPixmap);
            m_currentCaptureState = initCapture;
        }
    }
}

bool MainWindow::isPressPointInSelectRect(QPoint mousePressPoint)
{
    QRect selectRect = getRect(m_beginPoint, m_endPoint);
    if(selectRect.contains(mousePressPoint))
    {
        return true;
    }

    return false;
}

QRect MainWindow::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);

    if(selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if(selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}

QRect MainWindow::getMoveRect()
{
    QPoint movePoint = getMovePoint();
    QPoint beginPoint = m_beginPoint + movePoint;
    QPoint endPoint = m_endPoint + movePoint;
    if(m_currentCaptureState == finishMoveCaptureArea)
    {
        m_beginPoint = beginPoint;
        m_endPoint = endPoint;
        m_beginMovePoint = QPoint(0, 0);
        m_endMovePoint = QPoint(0, 0);
    }
    return getRect(beginPoint, endPoint);
}

QPoint MainWindow::getMovePoint()
{
    QPoint movePoint = m_endMovePoint - m_beginMovePoint;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    if(currentRect.topLeft().x() + movePoint.x() < 0)
    {
        movePoint.setX(0 - currentRect.topLeft().x());
    }
    if(currentRect.topLeft().y() + movePoint.y() < 0)
    {
        movePoint.setY(0 - currentRect.topLeft().y());
    }
    if(currentRect.bottomRight().x() + movePoint.x() > m_screenwidth)
    {
        movePoint.setX(m_screenwidth - currentRect.bottomRight().x());
    }
    if(currentRect.bottomRight().y() + movePoint.y() > m_screenheight)
    {
        movePoint.setY(m_screenheight - currentRect.bottomRight().y());
    }
    return movePoint;
}

QRect MainWindow::getSelectRect()
{
    if(m_currentCaptureState == beginCaptureImage || m_currentCaptureState == finishCaptureImage)
    {
        return getRect(m_beginPoint, m_endPoint);
    }
    else if(m_currentCaptureState == beginMoveCaptureArea || m_currentCaptureState == finishMoveCaptureArea)
    {
        return getMoveRect();
    }

    return QRect(0, 0, 0, 0);
}

QImage MainWindow::cvMatToQimage(const cv::Mat& mat)
{
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
             uchar *pDest = image.scanLine(row);
             memcpy(pDest, pSrc, mat.cols);
             pSrc += mat.step;
        }
        return image;
    }
    else if(mat.type() == CV_8UC3)
    {
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        //qDebug() << "CV_8UC4";
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
         return QImage();
    }
}

cv::Mat MainWindow::qimageToCvMat(QImage image)
{
    cv::Mat mat;
    qDebug() << image.format();
    switch(image.format())
    {
        case QImage::Format_ARGB32:
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32_Premultiplied:
            mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
            break;
        case QImage::Format_RGB888:
            mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            break;
        case QImage::Format_Indexed8:
             mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
              break;
    }
    return mat;
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("打开图片"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else
    {
        /*QImage* img=new QImage;
        if(! ( img->load(path) ) )
        {
            QMessageBox::information(this, tr("打开图像失败"), tr("打开图像失败!"));
            delete img;
            return;
        }*/
        image = imread(path.toStdString());
        image.copyTo(temColorImage);
        QImage* img=new QImage;
        *img = cvMatToQimage(image);
        m_screenheight = img->height();
        m_screenwidth = img->width();
        m_loadPixmap = QPixmap::fromImage(*img);
        ui->label->setPixmap(m_loadPixmap);
        working = true;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open Config"), "", tr("Config Files (*.png *.jpg *bmp)"));
    cv::imwrite(fileName.toStdString(), image);
}

void MainWindow::on_pushButton_3_clicked()
{
    double angle = -90;
    cv::Point2f center(image.cols / 2, image.rows / 2);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
    cv::Rect bbox = cv::RotatedRect(center, image.size(), angle).boundingRect();
    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    cv::Mat dst;
    cv::warpAffine(image, dst, rot, bbox.size());
    image = dst;
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_pushButton_4_clicked()
{
    double angle = 90;
    cv::Point2f center(image.cols / 2, image.rows / 2);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
    cv::Rect bbox = cv::RotatedRect(center, image.size(), angle).boundingRect();
    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    cv::Mat dst;
    cv::warpAffine(image, dst, rot, bbox.size());
    image = dst;
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_pushButton_5_clicked()
{
    Mat temp;
    flip(image, temp, 1);
    image = temp;
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}


void MainWindow::on_pushButton_6_clicked()
{
    Mat temp;
    flip(image, temp, 0);
    image = temp;
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    /*Mat new_image = Mat::zeros( image.size(), image.type() );
    int temx = image.rows;
    int temy = image.cols + image.cols*1/3;
    for( int x = 0; x < temy; x++ )
        {
            for( int y = 0; y < image.rows; y++ )
            {
                for( int c = 0; c < 3; c++ )
                {
                    new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( value*0.01*( image.at<Vec3b>(y,x)[c] ) );
                }
            }
        }
    tempColorImage = new_image;
    QImage img = cvMatToQimage(new_image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);*/
    int rows = temColorImage.rows;
    int cols = temColorImage.cols;
    for(int i = 0;i < rows;i++)
    {
        for(int  j = 0;j < cols;j++)
        {
            _I[i][j] = (value * 0.01 * I[i][j]);
            if(_I[i][j] >= 255)_I[i][j] = 255;
        }
    }
    HSI2RGB();
    refreshRGB();
    QImage img = cvMatToQimage(temColorImage);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    int rows = temColorImage.rows;
    int cols = temColorImage.cols;
    for(int i = 0;i < rows;i++)
    {
        for(int  j = 0;j < cols;j++)
        {
            _H[i][j] = value * 0.01 * H[i][j];
            if(_H[i][j] >= 360)_H[i][j] = 360;
        }
    }
    HSI2RGB();
    refreshRGB();
    QImage img = cvMatToQimage(temColorImage);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::getRGB(cv::Mat img)
{
    int rows = img.rows;
    int cols = img.cols;
    R = new int*[rows];
    G = new int*[rows];
    B = new int*[rows];
    for(int i = 0;i < rows;i++)
    {
        R[i] = new int[cols];
        G[i] = new int[cols];
        B[i] = new int[cols];
    }
    for(int i = 0;i < rows;i++)
    {
        for(int j = 0;j < cols;j++)
        {
            R[i][j] = img.at<Vec3b>(i,j)[2];
            G[i][j] = img.at<Vec3b>(i,j)[1];
            B[i][j] = img.at<Vec3b>(i,j)[0];
        }
    }
}

void MainWindow::getHSI(cv::Mat img)
{
    int rows = img.rows;
    int cols = img.cols;
    H = new double*[rows];
    S = new double*[rows];
    I = new double*[rows];
    _H = new double*[rows];
    _S = new double*[rows];
    _I = new double*[rows];
    for(int i = 0;i < rows;i++)
    {
        H[i] = new double[cols];
        S[i] = new double[cols];
        I[i] = new double[cols];
        _H[i] = new double[cols];
        _S[i] = new double[cols];
        _I[i] = new double[cols];
    }
    for(int i = 0;i < rows;i++)
    {
        for(int j = 0;j < cols;j++)
        {
            //H
            double numerator = ((R[i][j] - G[i][j]) + (R[i][j] - B[i][j])) / 2;
            double denominator = sqrt(pow((R[i][j] - G[i][j]), 2) + (R[i][j] - B[i][j])*(G[i][j] - B[i][j]));
            if (denominator == 0)
                H[i][j] = 0;
            else
            {
                double Theta = acos(numerator / denominator) * 180 / PI;
                if (B[i][j] <= G[i][j])
                     H[i][j] = Theta;
                else  H[i][j] = 360 - Theta;
            }
            //S
            int minvalue = B[i][j];
            if (minvalue > G[i][j]) minvalue = G[i][j];
            if (minvalue > R[i][j]) minvalue = R[i][j];
            numerator = 3 * minvalue;
            denominator = R[i][j] + G[i][j] + B[i][j];
            if (denominator == 0)  S[i][j] = 0;
            else
            {
                S[i][j] = 1 - numerator / denominator;
            }
            //I
            I[i][j] = (R[i][j] + G[i][j] + B[i][j]) / 3;

            _H[i][j] = H[i][j];
            _S[i][j] = S[i][j];
            _I[i][j] = I[i][j];
        }
    }
}

void MainWindow::delete1(int **X)
{
    int rows = image.rows;
    for(int i = 0;i < rows;i++)
    {
        delete[] X[i];
        X[i] = NULL;
    }
    delete[] X;
    X = NULL;
}

void MainWindow::delete2(double **X)
{
    int rows = image.rows;
    for(int i = 0;i < rows;i++)
    {
        delete[] X[i];
        X[i] = NULL;
    }
    delete[] X;
    X = NULL;
}

void MainWindow::HSI2RGB()
{
    int rows = temColorImage.rows;
    int cols = temColorImage.cols;
    double tem;
    for(int i = 0;i < rows;i++)
    {
        for(int j = 0;j < cols;j++)
        {
            if(_H[i][j] < 120 && _H[i][j] >= 0)
            {
                tem = _H[i][j] * PI / 180;
                B[i][j] = _I[i][j] * (1 - _S[i][j]);
                R[i][j] = _I[i][j] * (1 + (_S[i][j] * cos(tem))/cos(PI/3 - tem));
                G[i][j] = (3 * _I[i][j] - (B[i][j] + R[i][j]));
            }
            else if(_H[i][j] < 240 && _H[i][j] >= 120)
            {
                tem = _H[i][j] - 120;
                tem = tem * PI / 180;
                R[i][j] = _I[i][j] * (1 - _S[i][j]);
                G[i][j] = _I[i][j] * (1 + (_S[i][j] * cos(tem))/cos(PI/3 - tem));
                B[i][j] = (3 * _I[i][j] - (B[i][j] + R[i][j]));
            }
            else
            {
                tem = _H[i][j] - 240;
                tem = tem * PI / 180;
                G[i][j] = _I[i][j] * (1 - _S[i][j]);
                B[i][j] = _I[i][j] * (1 + (_S[i][j] * cos(tem))/cos(PI/3 - tem
                                                                    ));
                R[i][j] = (3 * _I[i][j] - (B[i][j] + R[i][j]));

            }
            R[i][j] = min(R[i][j], 255);
            G[i][j] = min(G[i][j], 255);
            B[i][j] = min(B[i][j], 255);
            /*double x1 = _H[i][j];
            double y1 = _S[i][j];
            double z1 = _I[i][j];
            int x = R[i][j];
            int y = G[i][j];
            int z = B[i][j];
            int ikk=0;*/
        }
    }
}

void MainWindow::refreshRGB()
{
    int rows = temColorImage.rows;
    int cols = temColorImage.cols;
    for(int i = 0;i < rows;i++)
    {

        for(int j = 0;j < cols;j++)
        {
            temColorImage.at<Vec3b>(i,j)[2] = R[i][j];
            temColorImage.at<Vec3b>(i,j)[1] = G[i][j];
            temColorImage.at<Vec3b>(i,j)[0] = B[i][j];
        }
    }
}

void MainWindow::checkAndDelete()
{
    if(H != NULL)
        delete2(H);
    if(S != NULL)
        delete2(S);
    if(I != NULL)
        delete2(I);
    if(_H != NULL)
        delete2(_H);
    if(_S != NULL)
        delete2(_S);
    if(_I != NULL)
        delete2(_I);
    if(R != NULL)
        delete1(R);
    if(G != NULL)
        delete1(G);
    if(B != NULL)
        delete1(B);
    H = NULL;
    S = NULL;
    I = NULL;
    _H = NULL;
    _S = NULL;
    _I = NULL;
    R = NULL;
    G = NULL;
    B = NULL;
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    int rows = temColorImage.rows;
    int cols = temColorImage.cols;
    for(int i = 0;i < rows;i++)
    {
        for(int  j = 0;j < cols;j++)
        {
            _S[i][j] = value * 0.01 * _S[i][j];
            if(_S[i][j] >= 1)_S[i][j] = 1;
        }
    }
    HSI2RGB();
    refreshRGB();
    QImage img = cvMatToQimage(temColorImage);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    if(H == NULL)
    {
        image.copyTo(temColorImage);
        getRGB(temColorImage);
        getHSI(temColorImage);
    }
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
}

void MainWindow::on_horizontalSlider_2_sliderPressed()
{
    if(H == NULL)
    {
        image.copyTo(temColorImage);
        getRGB(temColorImage);
        getHSI(temColorImage);
    }
}

void MainWindow::on_horizontalSlider_2_sliderReleased()
{
}

void MainWindow::on_horizontalSlider_3_sliderPressed()
{
    if(H == NULL)
    {
        image.copyTo(temColorImage);
        getRGB(temColorImage);
        getHSI(temColorImage);
    }
}

void MainWindow::on_horizontalSlider_3_sliderReleased()
{
}

void MainWindow::on_pushButton_7_clicked()
{
    temColorImage.copyTo(image);
    checkAndDelete();
}

void MainWindow::on_pushButton_8_clicked()
{
    image.copyTo(temColorImage);
    QImage img = cvMatToQimage(temColorImage);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
    checkAndDelete();
}

void MainWindow::circleColorful()
{
    Mat* temp = new Mat(image.rows, image.cols, image.type());
    Mat* temp2 = new Mat(image.rows, image.cols, image.type());
    Mat* temp3 = new Mat(image.rows, image.cols, image.type());
    int r = ui->lineEdit->text().toInt();
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            temp->at<Vec3b>(i, j)[0] = 255;
            temp->at<Vec3b>(i, j)[1] = 255;
            temp->at<Vec3b>(i, j)[2] = 255;
            temp2->at<Vec3b>(i, j)[0] = 255;
            temp2->at<Vec3b>(i, j)[1] = 255;
            temp2->at<Vec3b>(i, j)[2] = 255;
            temp3->at<Vec3b>(i, j)[0] = 255;
            temp3->at<Vec3b>(i, j)[1] = 255;
            temp3->at<Vec3b>(i, j)[2] = 255;
        }
    }

    int r1 = (r*blue) / 255.0;
    int r2 = (r*green) / 255.0;
    int r3 = (r*red) / 255.0;

    Point center;
    for (int i = 0; i < image.rows; i+=2*r1)
    {
        for (int j = 0; j < image.cols; j+= 2*r1)
        {
            center.x = i;
            center.y = j;
            circle(*temp, center, r1, cvScalar(image.at<Vec3b>(j, i)[0],255,255),-1);
        }
    }
    for (int i = 0; i < image.rows; i += 2 * r2)
    {
        for (int j = 0; j < image.cols; j += 2 * r2)
        {
            center.x = i;
            center.y = j;
            circle(*temp2, center, r2, cvScalar(255,image.at<Vec3b>(j, i)[1], 255),-1);
        }
    }
    for (int i = 0; i < image.rows; i += 2 * r3)
    {
        for (int j = 0; j < image.cols; j += 2 * r3)
        {
            center.x = i;
            center.y = j;
            circle(*temp3, center, r3, cvScalar(255,255,image.at<Vec3b>(j, i)[2]),-1);
        }
    }
    for (int i = 0; i < image.rows; i++)

    {
        for (int j = 0; j < image.cols; j++)
        {
            temp->at<Vec3b>(i, j)[1] = temp2->at<Vec3b>(i, j)[1];
            temp->at<Vec3b>(i, j)[2] = temp3->at<Vec3b>(i, j)[2];
        }
    }
    temp->copyTo(image);
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
    delete temp;
    delete temp2;
    delete temp3;
}

void MainWindow::getMean()
{
    int rows = image.rows;
    int cols = image.cols;
    red = 0;
    green = 0;
    blue = 0;
    /*uchar* pxvec = image.ptr<uchar>(0);
    for(int i = 0;i < rows;i++)
    {
        pxvec = image.ptr<uchar>(i);
        for(int j = 0;j < cols;j++)
        {
            blue += pxvec[j * 3];
            if (image.channels() == 3)
            {
                green += pxvec[j * 3 + 1];
                red += pxvec[j * 3 + 2];
            }
        }
    }*/
    for(int i = 0;i < rows;i++)
    {
        for(int j = 0;j < cols;j++)
        {
            red += image.at<Vec3b>(i,j)[2];
            green += image.at<Vec3b>(i,j)[1];
            blue += image.at<Vec3b>(i,j)[0];
        }
    }
    red = red / (rows * cols);
    green = green / (rows * cols);
    blue = blue / (rows * cols);
}

void MainWindow::on_pushButton_9_clicked()
{
    getMean();
    circleColorful();
}

void MainWindow::on_action_triggered()
{
    int cols = image.cols;
    int rows = image.rows;
    uchar *pImage;
    int minPix = 255;
    int maxPix = 0;
    for(int j = 0;j < rows;j++)
    {
        pImage = image.ptr<uchar>(j);
        for(int i = 0;i < cols;i++)
        {
            if(pImage[i] < minPix)
                minPix = pImage[i];
            if(pImage[i] > maxPix)
                maxPix = pImage[i];
        }
    }

    for(int j = 0;j < rows;j++)
    {
        pImage = image.ptr<uchar>(j);
        for(int i = 0;i < cols;i++)
        {
            pImage[i] = (pImage[i] - minPix) * 255 / (maxPix - minPix);
        }
    }
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_action_2_triggered()
{
    Dialog *myDialog = new Dialog;
    connect(myDialog, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
    myDialog->show();
}

 void MainWindow::receiveData(QString data)
 {
     int rows = image.rows;
     int cols = image.cols;
     for(int i = 0;i < rows;i++)
     {
         for(int j = 0;j < cols;j++)
         {
             double c = data.toDouble();
             
             double r = (double)(image.at<Vec3b>(i,j)[2]);
             double g = (double)(image.at<Vec3b>(i,j)[1]);
             double b = (double)(image.at<Vec3b>(i,j)[0]);
             double _r = c * log(1 + r);
             double _g = c * log(1 + g);
             double _b = c * log(1 + b);

             image.at<Vec3b>(i,j)[2] = saturate_cast<uchar>(_r);
             image.at<Vec3b>(i,j)[1] = saturate_cast<uchar>(_g);
             image.at<Vec3b>(i,j)[0] = saturate_cast<uchar>(_b);
         }
     }
     QImage img = cvMatToQimage(image);
     m_loadPixmap = QPixmap::fromImage(img);
     ui->label->setPixmap(m_loadPixmap);
 }

 void MainWindow::gammaTrans(QString data)
 {
     int rows = image.rows;
     int cols = image.cols;
     double gamma = data.toDouble();
     double c = pow(255, 1 - gamma);
     for(int i = 0;i < rows;i++)
     {
         for(int j = 0;j < cols;j++)
         {
             double r = (double)(image.at<Vec3b>(i,j)[2]);
             double g = (double)(image.at<Vec3b>(i,j)[1]);
             double b = (double)(image.at<Vec3b>(i,j)[0]);
             double _r = c * pow(r, gamma);
             double _g = c * pow(g, gamma);
             double _b = c * pow(b, gamma);



             image.at<Vec3b>(i,j)[2] = saturate_cast<uchar>(_r);
             image.at<Vec3b>(i,j)[1] = saturate_cast<uchar>(_g);
             image.at<Vec3b>(i,j)[0] = saturate_cast<uchar>(_b);
         }
     }
     QImage img = cvMatToQimage(image);
     m_loadPixmap = QPixmap::fromImage(img);
     ui->label->setPixmap(m_loadPixmap);
 }

void MainWindow::on_action_3_triggered()
{
    Dialog *myDialog = new Dialog;
    connect(myDialog, SIGNAL(sendData(QString)), this, SLOT(gammaTrans(QString)));
    myDialog->show();
}

void MainWindow::myEqualizeHist(CvArr* srcarr, CvArr* dstarr)
{
    CvMat sstub;
    CvMat dstub;
    CvMat *src = cvGetMat(srcarr, &sstub);
    CvMat *dst = cvGetMat(dstarr, &dstub);
    CvSize size = cvGetSize(src);

    int x, y;
    const int hist_size = 256;
    fill(p, p + hist_size, 0);
    for(y = 0; y < size.height; y++)
    {
        const uchar* sptr = src->data.ptr + src->step * y;
        for(x = 0; x < size.width; x++)
        {
            p[sptr[x]]++;
        }
     }

     int c[hist_size];
     c[0] = p[0];
     for(int i = 1; i < hist_size; i++)
     {
        c[i] = c[i - 1] + p[i];
     }

     uchar lut[hist_size];
     for(int i = 0; i < hist_size; i++)
     {
        int val = cvRound(c[i] * (255.f / (size.width * size.height)));
        lut[i] = saturate_cast<uchar>(val);
     }
     for(y = 0; y < size.height; y++)
     {
        const uchar* sptr = src->data.ptr + src->step * y;
        uchar* dptr = dst->data.ptr + dst->step * y;
        for(x = 0; x < size.width; x++)
        {
            dptr[x] = lut[sptr[x]];
        }
     }
     fill(dst_p, dst_p + hist_size, 0);
     for(y = 0; y < size.height; y++)
     {
        const uchar* dst_sptr = dst->data.ptr + dst->step * y;
        for(x = 0; x < size.width; x++)
        {
            dst_p[dst_sptr[x]]++;
       }
     }
}

void MainWindow::on_action_4_triggered()
{
    IplImage iplImage = image;
    IplImage *_image = &iplImage;
    IplImage* redImage = cvCreateImage(cvGetSize(_image), _image->depth, 1);
    IplImage* greenImage = cvCreateImage(cvGetSize(_image), _image->depth, 1);
    IplImage* blueImage = cvCreateImage(cvGetSize(_image), _image->depth, 1);

    cvSplit(_image, redImage, greenImage, blueImage, NULL);
    myEqualizeHist(redImage, redImage);
    myEqualizeHist(greenImage, greenImage);
    myEqualizeHist(blueImage, blueImage);
    cvMerge(blueImage, greenImage, redImage, NULL, _image);

    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_action_5_triggered()
{
    Dialog *myDialog = new Dialog;
    connect(myDialog, SIGNAL(sendData(QString)), this, SLOT(histogramMatch(QString)));
    myDialog->show();
}

void MainWindow::histogramMatch(QString path)
{
    Mat target = imread(path.toStdString());
    vector<Mat> rgb_image;
    split(image, rgb_image);
    vector<Mat> rgb_target;
    split(target, rgb_target);
    Mat *resultR;
    Mat *resultG;
    Mat *resultB;
    onedHistSpecify(&rgb_image[0], &rgb_target[0], resultR);
    onedHistSpecify(&rgb_image[1], &rgb_target[1], resultG);
    onedHistSpecify(&rgb_image[2], &rgb_target[2], resultB);
    cvMerge(resultB, resultG, resultR, NULL, &image);
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::onedHistSpecify(cv::Mat *src, cv::Mat *dst, cv::Mat *result)
{
    Mat src_hist;
    Mat dst_hist;
    int histSize = 255;
    float range[] = { 0, 255 } ;
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
    float src_cdf[256] = { 0 };
    float dst_cdf[256] = { 0 };

    calcHist( src, 1, 0, Mat(), src_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( dst, 1, 0, Mat(), dst_hist, 1, &histSize, &histRange, uniform, accumulate );
    src_hist /= (src->rows * src->cols);
    dst_hist /= (dst->rows * dst->cols);

    for (int i = 0; i < 256; i++)
        {
            if (i == 0)
            {
                src_cdf[i] = src_hist.at<float>(i);
                dst_cdf[i] = dst_hist.at<float>(i);
            }
            else
            {
                src_cdf[i] = src_cdf[i - 1] + src_hist.at<float>(i);
                dst_cdf[i] = dst_cdf[i - 1] + dst_hist.at<float>(i);
            }
        }
    float diff_cdf[256][256];
        for (int i = 0; i < 256; i++)
            for (int j = 0; j < 256; j++)
                diff_cdf[i][j] = fabs(src_cdf[i] - dst_cdf[j]);
    Mat lut(1, 256, CV_8U);
    for (int i = 0; i < 256; i++)
        {
            float min = diff_cdf[i][0];
            int index = 0;
            for (int j = 1; j < 256; j++)
            {
                if (min > diff_cdf[i][j])
                {
                    min = diff_cdf[i][j];
                    index = j;
                }
            }
            lut.at<uchar>(i) = static_cast<uchar>(index);
        }
    LUT(*src, lut, *result);
}


void MainWindow::on_action_6_triggered()
{
    Dialog *myDialog = new Dialog;
    connect(myDialog, SIGNAL(sendData(QString)), this, SLOT(midWave(QString)));
    myDialog->show();
}

void MainWindow::midWave(QString data)
{
    int _data = data.toInt();
    _data = (int)(_data/2);
    if(_data == 0)
        _data = 1;
    int *count = new int[_data * 4 + 1];
    int *count2 = new int[_data * 4 + 1];
    image.copyTo(temColorImage);
    for (int i = _data;i < (image.cols - _data);i++)
        {
            for (int j =_data; j< (image.rows-_data);j++)
            {
                count[0] = image.at<Vec3b>(i,j)[0];
                count2[0] = i * 1000 + j;
                for (int k=0;k<_data;k++)
                {
                    count[k*4+1] = image.at<Vec3b>(i-k-1,j-k-1)[0]+ image.at<Vec3b>(i - k - 1,j - k - 1)[1] + image.at<Vec3b>(i - k - 1,j - k - 1)[2] ;
                    count[k*4+2] = image.at<Vec3b>(i-k-1,j+k+1)[0]+ image.at<Vec3b>(i - k - 1,j + k + 1)[1]+ image.at<Vec3b>(i - k - 1,j + k + 1)[2];
                    count[k*4+3] = image.at<Vec3b>(i+k+1,j-k-1)[0]+ image.at<Vec3b>(i + k + 1,j - k - 1)[1]+ image.at<Vec3b>(i + k + 1,j - k - 1)[2];
                    count[k*4+4] = image.at<Vec3b>(i+k+1,j+k+1)[0]+ image.at<Vec3b>(i + k + 1,j + k + 1)[1]+ image.at<Vec3b>(i + k + 1,j + k + 1)[2];
                    count2[k * 4 + 1] = (i - k - 1) * 1000 + (j - k - 1);
                    count2[k * 4 + 2] = (i - k - 1) * 1000 + (j + k + 1);
                    count2[k * 4 + 3] = (i + k + 1) * 1000 + (j - k - 1);
                    count2[k * 4 + 4] = (i + k + 1) * 1000 + (j + k + 1);
                }
                bool flag = true;
                while (flag)
                {
                    flag = false;
                    for (int m=0;m<4*_data;m++)
                    {
                        if (count[m]<count[m+1])
                        {
                            flag = true;
                            break;
                        }
                    }
                    for (int m = 0;m < 4 * _data;m++)
                    {
                        if (count[m] < count[m + 1])
                        {
                            int tmp = count[m];
                            count[m] = count[m + 1];
                            count[m + 1] = tmp;
                            tmp = count2[m];
                            count2[m] = count2[m + 1];
                            count2[m + 1] = tmp;
                        }
                    }
                }
                int x = count2[2 * _data] / 1000;
                int y = count2[2 * _data] % 1000;
                temColorImage.at<Vec3b>(i, j)[0] = image.at<Vec3b>(x, y)[0];
                temColorImage.at<Vec3b>(i, j)[1] = image.at<Vec3b>(x, y)[1];
                temColorImage.at<Vec3b>(i, j)[2] = image.at<Vec3b>(x, y)[2];
            }
        }
        temColorImage.copyTo(image);
        QImage img = cvMatToQimage(image);
        m_loadPixmap = QPixmap::fromImage(img);
        ui->label->setPixmap(m_loadPixmap);
        delete []count;
        delete []count2;
}


void MainWindow::on_action_7_triggered()
{
    Dialog *myDialog = new Dialog;
    connect(myDialog, SIGNAL(sendData(QString)), this, SLOT(guassWave(QString)));
    myDialog->show();
}

void MainWindow::guassWave(QString data)
{
    int _data = data.toInt();
    _data = (int)(_data/2);
    if(_data == 0)
        _data = 1;
    double *count = new double[_data * 2 + 1];
    double theta = 1 / (2 * PI);
    double summury=0;
    image.copyTo(temColorImage);
    for (int k = 0;k <= _data;k++)
        {
            count[_data+k] = exp(0 - k*k / 2) / theta;
            count[_data-k] = exp(0 - k*k / 2) / theta;
            summury += (2 * count[_data - k]);
        }
        for (int i = _data;i < image.cols - _data;i++)
        {
            for (int j = _data; j < image.rows - _data;j++)
            {
                double temb = 0;
                double temg = 0;
                double temr = 0;
                for (int k=0; k<2*_data+1;k++)
                {
                    temb += count[k] * (double)image.at<Vec3b>(i - _data + k, j)[0];
                    temg += count[k] * (double)image.at<Vec3b>(i - _data + k, j)[1];
                    temr += count[k] * (double)image.at<Vec3b>(i - _data + k, j)[2];
                }
                temColorImage.at<Vec3b>(i,j)[0] = saturate_cast<uchar>(temb / summury);
                temColorImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(temg / summury);
                temColorImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(temr / summury);
            }
        }
        for (int i = _data;i < image.cols - _data;i++)
        {
            for (int j = _data; j < image.rows - _data;j++)
            {
                double temb = 0;
                double temg = 0;
                double temr = 0;
                for (int k = 0; k < 2 * _data + 1;k++)
                {
                    temb += count[k] * (double)image.at<Vec3b>(i , j - _data + k)[0];
                    temg += count[k] * (double)image.at<Vec3b>(i , j - _data + k)[1];
                    temr += count[k] * (double)image.at<Vec3b>(i , j - _data + k)[2];
                }
                temColorImage.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(temb / summury);
                temColorImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(temg / summury);
                temColorImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(temr / summury);
            }
        }
        temColorImage.copyTo(image);
        QImage img = cvMatToQimage(image);
        m_loadPixmap = QPixmap::fromImage(img);
        ui->label->setPixmap(m_loadPixmap);
        delete count;
}

void MainWindow::on_action_8_triggered()
{
    int data = 1;
    image.copyTo(temColorImage);
    for (int i = 1;i < image.rows - data;i++)
    {
         for (int j = 1; j < image.cols - data;j++)
         {
                temColorImage.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(abs(3 * image.at<Vec3b>(i, j)[0] - image.at<Vec3b>(i, j + 1)[0] - image.at<Vec3b>(i + 1, j)[0] ));
                temColorImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(abs(3 * image.at<Vec3b>(i, j)[1] - image.at<Vec3b>(i, j + 1)[1] - image.at<Vec3b>(i + 1, j)[1] ));
                temColorImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(abs(3 * image.at<Vec3b>(i, j)[2] - image.at<Vec3b>(i, j + 1)[2] - image.at<Vec3b>(i + 1, j)[2] ));
         }
    }
    temColorImage.copyTo(image);
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_action_9_triggered()
{
    image.copyTo(temColorImage);
    srand(time(NULL));
    int rows = image.rows;
    int cols = image.cols;
    Mat tem = Mat::zeros(cols ,rows , image.type());
    int x = 0;
    int y = 0;
    int r = 0;
    for (int i=0;i<1000;i++)
    {
         x = rand() % (rows);
         y = rand() % (cols);
         r = rand() % (10);
            for (int x1=x;x1<min(x+r,rows);x1++)
            {
                for (int y1=y;y1<min(cols,y+r);y1++)
                {
                    tem.at<Vec3b>(x1, y1)[0] = 255;
                    tem.at<Vec3b>(x1, y1)[1] = 255;
                    tem.at<Vec3b>(x1, y1)[2] = 255;
                }
            }
        }
        int param = 3;
        for (int i = param;i < image.rows - param;i++)
        {
            for (int j = param; j < image.cols - param;j++)
            {
                int R_ = 0;
                int G_ = 0;
                int B_ = 0;
                for (int k=0-param;k<=param;k++)
                {
                    B_ += tem.at<Vec3b>(i + k, j + k)[0];
                    G_ += tem.at<Vec3b>(i + k, j + k)[1];
                    R_ += tem.at<Vec3b>(i + k, j + k)[2];
                }
                tem.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(B_/(2*param+1));
                tem.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(G_ / (2 * param + 1));
                tem.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(R_ / (2 * param + 1));
            }
        }
        for (int i = 0;i < image.rows ;i++)
        {
            for (int j = 0; j < image.cols;j++)
            {
                temColorImage.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(image.at<Vec3b>(i, j)[0] + tem.at<Vec3b>(i, j)[0] - (image.at<Vec3b>(i, j)[0] * tem.at<Vec3b>(i, j)[0]) / 255);
                temColorImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(image.at<Vec3b>(i, j)[1] + tem.at<Vec3b>(i, j)[1] - (image.at<Vec3b>(i, j)[1] * tem.at<Vec3b>(i, j)[1]) / 255);
                temColorImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(image.at<Vec3b>(i, j)[2] + tem.at<Vec3b>(i, j)[2] - (image.at<Vec3b>(i, j)[2] * tem.at<Vec3b>(i, j)[2]) / 255);
            }
        }
        temColorImage.copyTo(image);
        QImage img = cvMatToQimage(image);
        m_loadPixmap = QPixmap::fromImage(img);
        ui->label->setPixmap(m_loadPixmap);
}


void MainWindow::on_action_10_triggered()
{
    Dialog *myDialog = new Dialog;
    connect(myDialog, SIGNAL(sendData(QString)), this, SLOT(smoothWave(QString)));
    myDialog->show();
}

void MainWindow::smoothWave(QString data)
{
    image.copyTo(temColorImage);
    QString data1 = data.section(',', 0, 0);
    QString data2 = data.section(',', 1, 1);
    int _data1 = data1.toInt();
    double _data2 = data2.toDouble();
    for (int c=0; c<3;c++)
    {
        Mat img(image.rows, image.cols, CV_8U);
        for (int i = 0; i < image.rows;i++)
        {
                for (int j = 0;j < image.cols;j++)
                {
                        img.at<uchar>(i, j) = image.at<Vec3b>(i, j)[c];
                }
         }
         int M = getOptimalDFTSize(img.rows);
         int N = getOptimalDFTSize(img.cols);
         Mat padded;
         copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));

         Mat plane[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
         Mat complexImg;
         merge(plane, 2, complexImg);

        dft(complexImg, complexImg);

        std::vector<Mat> channels;
        split(complexImg, channels);
        for (int k=0;k<=1;k++)
        {
            Mat mag = channels[k];
            mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
            int cx = mag.cols / 2;
            int cy = mag.rows / 2;

            Mat tem;
            Mat q0(mag, Rect(0, 0, cx, cy));
            Mat q1(mag, Rect(cx, 0, cx, cy));
            Mat q2(mag, Rect(0, cy, cx, cy));
            Mat q3(mag, Rect(cx, cy, cx, cy));
            q0.copyTo(tem);
            q3.copyTo(q0);
            tem.copyTo(q3);
            q1.copyTo(tem);
            q2.copyTo(q1);
            tem.copyTo(q2);
            for (int y = 0; y < mag.rows; y++) {
                for (int x = 0; x < mag.cols; x++) {
                    double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
                    double h = 1.0 / (1 + pow(d / _data2, 2 * _data1));
                    mag.at<float>(x, y) *= h;
                }}
            q0.copyTo(tem);
            q3.copyTo(q0);
            tem.copyTo(q3);
            q1.copyTo(tem);
            q2.copyTo(q1);
            tem.copyTo(q2);
        }
        merge(channels, complexImg);
        Mat invDFT, invDFTcvt;
        idft(complexImg, invDFT, DFT_SCALE | DFT_REAL_OUTPUT);
        invDFT.convertTo(invDFTcvt, CV_8U);
        for (int i = 0; i < image.rows;i++)
        {
            for (int j = 0;j < image.cols;j++)
            {
                temColorImage.at<Vec3b>(i, j)[c] = invDFTcvt.at<uchar>(i, j);
            }
        }
    }
    temColorImage.copyTo(image);
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_action_11_triggered()
{
    Dialog *myDialog = new Dialog;
    connect(myDialog, SIGNAL(sendData(QString)), this, SLOT(sharpenWave(QString)));
    myDialog->show();
}

void MainWindow::sharpenWave(QString data)
{
    image.copyTo(temColorImage);
    QString data1 = data.section(',', 0, 0);
    QString data2 = data.section(',', 1, 1);
    int _data1 = data1.toInt();
    double _data2 = data2.toDouble();
    for (int c = 0; c<3;c++)
    {
        Mat img(image.rows, image.cols, CV_8U);
        for (int i = 0; i < image.rows;i++)
        {
              for (int j = 0;j < image.cols;j++)
              {
                  img.at<uchar>(i, j) = image.at<Vec3b>(i, j)[c];
              }
        }
            int M = getOptimalDFTSize(img.rows);
            int N = getOptimalDFTSize(img.cols);
            Mat padded;
            copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
            Mat plane[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
            Mat complexImg;
            merge(plane, 2, complexImg);
            dft(complexImg, complexImg);
            std::vector<Mat> channels;
            split(complexImg, channels);
            for (int k = 0;k <= 1;k++)
            {
                Mat mag = channels[k];

                mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
                int cx = mag.cols / 2;
                int cy = mag.rows / 2;

                Mat tem;
                Mat q0(mag, Rect(0, 0, cx, cy));
                Mat q1(mag, Rect(cx, 0, cx, cy));
                Mat q2(mag, Rect(0, cy, cx, cy));
                Mat q3(mag, Rect(cx, cy, cx, cy));

                q0.copyTo(tem);
                q3.copyTo(q0);
                tem.copyTo(q3);
                q1.copyTo(tem);
                q2.copyTo(q1);
                tem.copyTo(q2);
                for (int y = 0; y < mag.rows; y++) {

                    for (int x = 0; x < mag.cols; x++) {
                        double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
                        double h = 1.0 / (1 + pow(_data2 / d, 2 * _data1));
                        mag.at<float>(x, y) = mag.at<float>(x, y)*h + mag.at<float>(x, y);
                    }
                }
                q0.copyTo(tem);
                q3.copyTo(q0);
                tem.copyTo(q3);
                q1.copyTo(tem);
                q2.copyTo(q1);
                tem.copyTo(q2);
            }
            merge(channels, complexImg);
            Mat invDFT, invDFTcvt;
            idft(complexImg, invDFT, DFT_SCALE | DFT_REAL_OUTPUT);
            invDFT.convertTo(invDFTcvt, CV_8U);
            for (int i = 0; i < image.rows;i++)
            {
                for (int j = 0;j < image.cols;j++)
                {
                    temColorImage.at<Vec3b>(i, j)[c] = invDFTcvt.at<uchar>(i, j);
                }
            }
    }
    temColorImage.copyTo(image);
    QImage img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_action_12_triggered()
{
    int width = image.cols;
    int heigh = image.rows;
    RNG rng;
    Mat img(image.size(),CV_8UC3);
    for (int y=1; y<heigh-1; y++)
    {
        uchar* P0  = image.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=1; x<width-1; x++)
        {
            int tem=rng.uniform(0,9);
            P1[3*x]=image.at<uchar>(y-1+tem/3,3*(x-1+tem%3));
            P1[3*x+1]=image.at<uchar>(y-1+tem/3,3*(x-1+tem%3)+1);
            P1[3*x+2]=image.at<uchar>(y-1+tem/3,3*(x-1+tem%3)+2);
        }
    }
    img.copyTo(image);
    QImage _img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(_img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_action_13_triggered()
{
    int width=image.cols;
    int heigh=image.rows;
    RNG rng;
    Mat img(image.size(),CV_8UC3);
    for (int y=0; y<heigh; y++)
    {
        uchar* P0  = image.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=0.272*R+0.534*G+0.131*B;
            float newG=0.349*R+0.686*G+0.168*B;
            float newR=0.393*R+0.769*G+0.189*B;
            if(newB<0)newB=0;
            if(newB>255)newB=255;
            if(newG<0)newG=0;
            if(newG>255)newG=255;
            if(newR<0)newR=0;
            if(newR>255)newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }
    }
    img.copyTo(image);
    QImage _img = cvMatToQimage(image);
    m_loadPixmap = QPixmap::fromImage(_img);
    ui->label->setPixmap(m_loadPixmap);
}

void MainWindow::on_actionLOMO_triggered()
{
    image.copyTo(temColorImage);
    Mat img = Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; y++)
        {
            for (int x = 0; x < image.cols; x++)
            {
                img.at<Vec3b>(y, x)[0] = 10 * sqrt(image.at<Vec3b>(y, x)[0]);
                img.at<Vec3b>(y, x)[1] = 10 * sqrt(image.at<Vec3b>(y, x)[1]);
                img.at<Vec3b>(y, x)[2] = 10 * sqrt(image.at<Vec3b>(y, x)[2]);

            }
        }
        Mat res, roi, reverse_roi, reverse_res;
        res = Mat::zeros(image.size(), image.type());
        reverse_res = Mat::zeros(image.size(), image.type());
        roi = Mat::zeros(image.size(), CV_8UC1);
        reverse_roi = Mat(image.size(), CV_8UC1);
        for (int y = 0; y < reverse_roi.rows; y++)
        {
            for (int x = 0; x < reverse_roi.cols; x++)
            {
                reverse_roi.at<uchar>(y, x) = 255;
            }
        }
        int thickness = 20;
        int lineType = 8;
        double w = image.rows;
        double radio = w / 2.5;
        circle(roi,Point(w / 2.0, w / 2.0),radio,Scalar(255),thickness,lineType);
        circle(reverse_roi, Point(w / 2.0, w / 2.0), radio, Scalar(0), thickness, lineType);
        floodFill(reverse_roi, Point(w / 2, w / 2), Scalar(0));
        floodFill(roi, Point(w / 2, w / 2), Scalar(255));
        for (int y = 0; y < image.rows; y++)
        {
            for (int x = 0; x < image.cols; x++)
            {
                for (int c = 0;c < image.channels();c++)
                {
                    temColorImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(temColorImage.at<Vec3b>(y, x)[c] * 2);
                }
            }
        }
        temColorImage.copyTo(res, roi);
        temColorImage.copyTo(reverse_res, reverse_roi);
        reverse_res = reverse_res + res;
        double dst = 0;
        for (int y = 0; y < image.rows; y++)
        {
            for (int x = 0; x < image.cols; x++)
            {
                dst = (x - w / 2.0)*(x - w / 2.0) + (y - w / 2.0)*(y - w / 2.0);
                if (dst > radio*radio)
                {
                    for (int c = 0;c < image.channels();c++)
                    {
                        reverse_res.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(reverse_res.at<Vec3b>(y, x)[c] * pow((radio*radio) / dst, 2));
                    }
                }
            }
        }
        reverse_res.copyTo(image);
        QImage _img = cvMatToQimage(image);
        m_loadPixmap = QPixmap::fromImage(_img);
        ui->label->setPixmap(m_loadPixmap);
}
