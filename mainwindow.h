#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QDebug>
#include <QSlider>
#include <QPainter>
#include <iostream>
#include <QPainter>

using namespace std;
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
public slots:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int checked = -1;

    Point rect1;
    Point rect2;
    Point sqr1;
    Point sqr2;
    Point center;
    Point Trect1;
    Point Trect2;
    Point Tsqr1;
    Point Tsqr2;
    Point Tcenter;
    int Tradius;
    int radius;
    int ratio;


    bool startRect = true;
    bool startSqr = true;
    bool startCircle = true;

private slots:
    void updateWindow();
    void openWebcam();
    void closeWebcam();
    void reset(int);
    void ratioReset();

    void on_pushButton_clicked();
    void on_rectangle_stateChanged();
    void on_square_stateChanged();
    void on_circle_stateChanged();
    void on_up_clicked();
    void on_left_clicked();
    void on_right_clicked();
    void on_down_clicked();
    void on_reset_clicked();
    void on_size_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    VideoCapture cap;
    Mat frame;
    QImage qt_image;
};
#endif // MAINWINDOW_H
