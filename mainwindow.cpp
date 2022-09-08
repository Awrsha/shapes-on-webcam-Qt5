#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    cap.open(0);
    if(checked == 1)
    {
        closeWebcam();
        checked *= -1;
    }
    if(cap.isOpened())
    {
        openWebcam();
        checked *= -1;
    }
}

void MainWindow::updateWindow()
{
    cap >> frame;
    cvtColor(frame, frame, COLOR_BGR2RGB);
    on_rectangle_stateChanged();
    on_square_stateChanged();
    on_circle_stateChanged();
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qt_image));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::ratioReset()
{
    if(ui->rectangle->isChecked())
    {
        Trect1.x = rect1.x;
        Trect1.y = rect1.y;
        Trect2.x = rect2.x;
        Trect2.y = rect2.y;
    }

    if(ui->square->isChecked())
    {
        Tsqr1.x = sqr1.x;
        Tsqr1.y = sqr1.y;
        Tsqr2.x = sqr2.x;
        Tsqr2.y = sqr2.y;
    }

    if(ui->circle->isChecked())
    {
        Tcenter.x = center.x;
        Tcenter.y = center.y;
        Tradius = radius;

    }
}

void MainWindow::closeWebcam()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
    cap.release();
    Mat image = Mat::zeros(frame.size(),CV_8UC3);
    qt_image = QImage((const unsigned char*) (image.data), image.cols, image.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qt_image));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::openWebcam()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
    timer->start(1);
}

void MainWindow::reset(int n)
{
    if(n == 1)
    {
        rect1.x = frame.cols / 2 - 30 - (ratio + 1);
        rect1.y = frame.rows / 3 - (ratio + 1);
        rect2.x = frame.cols / 2 + 30 + (ratio + 1);
        rect2.y = frame.rows * 2 / 3 + (ratio + 1);
    }

    if(n == 2)
    {
        sqr1.x = frame.cols / 2 - 40 - (ratio + 1);
        sqr1.y = frame.rows / 2 - 40 - (ratio + 1);
        sqr2.x = frame.cols / 2 + 40 + (ratio + 1);
        sqr2.y = frame.rows / 2 + 40 + (ratio + 1);
    }

    if(n == 3)
    {
        center.x = frame.cols / 2;
        center.y = frame.rows / 2;
        radius = 50 + (ratio + 1);
    }

}

void MainWindow::on_rectangle_stateChanged()
{

    if(ui->rectangle->isChecked())
    {
        if(startRect == true)
        {
            reset(1);
        }
        else
        {
            void ratioReset();
        }
        rectangle(frame, rect1, rect2, Scalar(200,0,0), 2);

    }
}

void MainWindow::on_square_stateChanged()
{

    if(ui->square->isChecked())
    {
        if(startSqr == true)
        {
            reset(2);
        }
        rectangle(frame, sqr1, sqr2, Scalar(0,0,200), 2);
    }
}

void MainWindow::on_circle_stateChanged()
{

    if(ui->circle->isChecked())
    {
        if(startCircle == true)
        {
            reset(3);
        }
        circle(frame, center, radius, Scalar(50,200,70), 2);
    }
}

void MainWindow::on_up_clicked()
{
    if(ui->rectangle->isChecked())
    {
        rect1.y -= 50;
        rect2.y -= 50;
        Trect1.x = rect1.x + (ratio + 1);
        Trect1.y = rect1.y + (ratio + 1);
        Trect2.x = rect2.x - (ratio + 1);
        Trect2.y = rect2.y - (ratio + 1);
        startRect = false;
    }

    if(ui->square->isChecked())
    {
        sqr1.y -= 50;
        sqr2.y -= 50;
        Tsqr1.x = sqr1.x + (ratio + 1);
        Tsqr1.y = sqr1.y + (ratio + 1);
        Tsqr2.x = sqr2.x - (ratio + 1);
        Tsqr2.y = sqr2.y - (ratio + 1);

        startSqr = false;
    }

    if(ui->circle->isChecked())
    {
        center.y -= 50;
        Tradius = radius;
        startCircle = false;
    }

}

void MainWindow::on_left_clicked()
{
    if(ui->rectangle->isChecked())
    {
        rect1.x -= 50;
        rect2.x -= 50;
        Trect1.x = rect1.x + (ratio + 1);
        Trect1.y = rect1.y + (ratio + 1);
        Trect2.x = rect2.x - (ratio + 1);
        Trect2.y = rect2.y - (ratio + 1);
        startRect = false;
    }

    if(ui->square->isChecked())
    {
        sqr1.x -= 50;
        sqr2.x -= 50;
        Tsqr1.x = sqr1.x + (ratio + 1);
        Tsqr1.y = sqr1.y + (ratio + 1);
        Tsqr2.x = sqr2.x - (ratio + 1);
        Tsqr2.y = sqr2.y - (ratio + 1);
        startSqr = false;
    }

    if(ui->circle->isChecked())
    {
        center.x -= 50;
        Tcenter.x = center.x;
        Tcenter.y = center.y;
        startCircle = false;
    }
}

void MainWindow::on_right_clicked()
{
    if(ui->rectangle->isChecked())
    {
        rect1.x += 50;
        rect2.x += 50;
        Trect1.x = rect1.x + (ratio + 1);
        Trect1.y = rect1.y + (ratio + 1);
        Trect2.x = rect2.x - (ratio + 1);
        Trect2.y = rect2.y - (ratio + 1);
        startRect = false;
    }

    if(ui->square->isChecked())
    {
        sqr1.x += 50;
        sqr2.x += 50;
        Tsqr1.x = sqr1.x + (ratio + 1);
        Tsqr1.y = sqr1.y + (ratio + 1);
        Tsqr2.x = sqr2.x - (ratio + 1);
        Tsqr2.y = sqr2.y - (ratio + 1);
        startSqr = false;
    }

    if(ui->circle->isChecked())
    {
        center.x += 50;
        Tcenter.x = center.x;
        Tcenter.y = center.y;
        startCircle = false;
    }
}

void MainWindow::on_down_clicked()
{
    if(ui->rectangle->isChecked())
    {
        rect1.y += 50;
        rect2.y += 50;
        Trect1.x = rect1.x + (ratio + 1);
        Trect1.y = rect1.y + (ratio + 1);
        Trect2.x = rect2.x - (ratio + 1);
        Trect2.y = rect2.y - (ratio + 1);
        startRect = false;
    }

    if(ui->square->isChecked())
    {
        sqr1.y += 50;
        sqr2.y += 50;
        Tsqr1.x = sqr1.x + (ratio + 1);
        Tsqr1.y = sqr1.y + (ratio + 1);
        Tsqr2.x = sqr2.x - (ratio + 1);
        Tsqr2.y = sqr2.y - (ratio + 1);
        startSqr = false;
    }

    if(ui->circle->isChecked())
    {
        center.y += 50;
        Tcenter.x = center.x;
        Tcenter.y = center.y;
        startCircle = false;
    }
}

void MainWindow::on_reset_clicked()
{
    if(ui->rectangle->isChecked())
    {
        reset(1);
    }

    if(ui->square->isChecked())
    {
        reset(2);
    }

    if(ui->circle->isChecked())
    {
        reset(3);
    }
}

void MainWindow::on_size_valueChanged(int value)
{
//    Trect1.x = rect1.x;
//    Trect1.y = rect1.y;
//    Trect1.x = rect1.x;
//    Trect2.y = rect2.y;

    ratio = ui->size->value();
    if(ui->rectangle->isChecked() && startRect == false)
    {

        rect1.x = Trect1.x - (ratio + 1);
        rect1.y = Trect1.y - (ratio + 1);
        rect2.x = Trect2.x + (ratio + 1);
        rect2.y = Trect2.y + (ratio + 1);

    }

    if(ui->square->isChecked() && startSqr == false)
    {
        sqr1.x = Tsqr1.x - (ratio + 1);
        sqr1.y = Tsqr1.y - (ratio + 1);
        sqr2.x = Tsqr2.x + (ratio + 1);
        sqr2.y = Tsqr2.y + (ratio + 1);
    }

    if(ui->circle->isChecked() && startCircle == false)
    {
        radius = Tradius + (ratio + 1);
    }
}
