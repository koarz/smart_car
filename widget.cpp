#include "widget.h"
#include "ui_widget.h"


#include <QTime>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QGraphicsRotation>
#include <QThread>
#include <cmath>
#include <iostream>


Widget::Widget(QWidget *parent) :
    QWidget(parent), car_control(*this), light(*this),
    ui(new Ui::Widget)
{
    ;
    ui->setupUi(this);
    Init();
}

Widget::~Widget()
{
    delete ui;
}

//初始化红绿灯状态
void Widget::Init() {
    ui->Green_Led->show();
    ui->Red_Led->hide();
    ui->Yellow_Led->hide();
//    ui->barrier_car->hide();
    QTransform matrix;
    matrix.rotate(-90);
    QPixmap pix = QPixmap(":/images/parking.png").transformed(matrix, Qt::SmoothTransformation);
    ui->label_13->setPixmap(pix);
    matrix.rotate(-90);
    pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
    ui->barrier_car_2->setPixmap(pix);
    ui->label_10->hide();
}

//start按钮点击事件
void Widget::on_pushButton_clicked()
{
    if (buttonIsClinked) {
        return;
    } else {
        buttonIsClinked = true;
    }
    car_control.start();
    light.start();
}

//小车混流行驶
void Widget::run1() {
    //设定小车行走路线
    for(int i = ui->label_2->y(); i < 650; i++){
        ui->label_2->setGeometry(ui->label_2->x(),i,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        if (i < 500) {
            sleep(10);
        } else {
            sleep(20);

            QTransform matrix;
            matrix.rotate((i - 500) * -0.6);                   //实现左转
            QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
            ui->label_2->setPixmap(pix);
            ui->label_2->setGeometry(ui->label_2->x() + 1, ui->label_2->y(),
                                     ui->label_2->width()
                                     ,ui->label_2->height());
        }
    }

    // ui->barrier_car->show();

    //x = 550 为红绿灯的坐标

    for (int i = ui->label_2->x();i <= 400; i++) {
        ui->label_2->setGeometry(i,ui->label_2->y(),
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        if (i < 300) {
            sleep(10);
        } else {
            sleep(5);
            if (i < 350) {
                QTransform matrix;
                matrix.rotate(-90 + (i - 300) * -0.225);                      //向左变道
                QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
                ui->label_2->setPixmap(pix);
                ui->label_2->setGeometry(i, ui->label_2->y() - 0.00001,
                                         ui->label_2->width()
                                         ,ui->label_2->height());
            } else {
                QTransform matrix;
                matrix.rotate(-101.25 + (i - 350) * 0.225);                   //方向回正
                QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
                ui->label_2->setPixmap(pix);
            }
        }
    }
    for (int i = ui->label_2->x(); i <= 550; i++) {
        if (i < 450) {
            QTransform matrix;
            matrix.rotate(-90 + (i - 400) * 0.225);
            QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
            ui->label_2->setPixmap(pix);
            ui->label_2->setGeometry(i, ui->label_2->y() + 0.5,
                                     ui->label_2->width()
                                     ,ui->label_2->height());
        } else  if (i < 500) {
            ui->label_2->setGeometry(i, ui->label_2->y() + 1,
                                     ui->label_2->width()
                                     ,ui->label_2->height());
        } else {
            QTransform matrix;
            matrix.rotate(-78.75 + (i - 500) * -0.225);
            QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
            ui->label_2->setPixmap(pix);
            ui->label_2->setGeometry(i, ui->label_2->y(),
                                     ui->label_2->width()
                                     ,ui->label_2->height());
        }
        sleep(10);
    }
    run2();
}

void Widget::run2() {
    // check light status until green light
    while (light_status != 0) {
        sleep(1);
    }
    for (int i = ui->label_2->x(); i <= 770; i++) {
        ui->label_2->setGeometry(i, ui->label_2->y(),
                                ui->label_2->width()
                                ,ui->label_2->height());
        sleep(10);
    }

    // car is on circle
    for (int i = ui->label_2->x(); i < 830; i++) {
        // turn on the right
        QTransform matrix;
        matrix.rotate(-90 + (i - 770) * 1.25);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        ui->label_2->setGeometry(i, ui->label_2->y() + 0.25,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }
    // TODO: The circle road may just use a useful function is enough

    // x move down and right and always turn left
    // the circle center is 1090 640
    for (int i = ui->label_2->x(); i < 1090; i++) {
        // turn on the right
        QTransform matrix;
        matrix.rotate(-27.5 + (i - 830) * -0.346);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        auto [next_x, next_y] = caculate_oncircle(ui->label_2->x(), ui->label_2->y());
        ui->label_2->setGeometry(next_x, next_y,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }
    for (int i = ui->label_2->x(); i < 1350; i++) {
        // turn on the right
        QTransform matrix;
        matrix.rotate(-90 + (i - 1090) * -0.346);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        auto [next_x, next_y] = caculate_oncircle(ui->label_2->x(), ui->label_2->y());
        ui->label_2->setGeometry(next_x, next_y,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }
    for (int i = ui->label_2->x(); i > 1140; i--) {
        // turn on the right
        QTransform matrix;
        matrix.rotate(-180 + (1350 - i) * -0.346);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        auto [next_x, next_y] = caculate_oncircle(i, ui->label_2->y());
        ui->label_2->setGeometry(next_x, 1280 - next_y,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }
    // for go out the circle x to 1100
    for (int i = ui->label_2->x(); i > 1115; i--) {
        QTransform matrix;
        matrix.rotate(-263 + (1140 - i) * 1.5);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        auto [next_x, next_y] = caculate_oncircle(i, ui->label_2->y() - 1);
        ui->label_2->setGeometry(next_x, 1280 - next_y,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }
    // fix directional
    for (int i = ui->label_2->y(); i > 350; i--) {
        QTransform matrix;
        matrix.rotate(-225 + (379 - i) * 1.5);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        ui->label_2->setGeometry(ui->label_2->x(), i,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }
    {
        QTransform matrix;
        matrix.rotate(-180);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
    }
    // go throurh and people start
    for (int i = ui->label_2->y(); i > 170; i--) {
        ui->label_2->setGeometry(ui->label_2->x(), i,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }
    ui->label_10->show();
    for (int i = ui->label_10->x(); i > 1060; i--) {
        ui->label_10->setGeometry(i, ui->label_10->y(),
                                 ui->label_10->width()
                                 ,ui->label_10->height());
        sleep(10);
    }
    ui->label_10->hide();
    // turn right
    for (int i = ui->label_2->y(); i > 70; i--) {
        QTransform matrix;
        matrix.rotate(-180 + (170 - i) * 0.9);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        ui->label_2->setGeometry(ui->label_2->x() + 1, i,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(20);
    }
    // go through
    for (int i = ui->label_2->x(); i < 1380; i++) {
        ui->label_2->setGeometry(i, ui->label_2->y(),
                                  ui->label_2->width()
                                  ,ui->label_2->height());
        sleep(10);
    }
    // end 倒车入库
    // x 1320 y 140
    for (int i = ui->label_2->y(); i < 140; i++) {
        QTransform matrix;
        matrix.rotate(-90 + (i - 70) * -1.3);
        QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
        ui->label_2->setPixmap(pix);
        ui->label_2->setGeometry(ui->label_2->x() - 0.00001, i,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(20);
    }
    ui->label_2->setGeometry(1320, 140,
                             ui->label_2->width()
                             ,ui->label_2->height());
}

// the function just a easy caculate function
// more complex and reasonable calculations require the inclusion of angle calculations
std::pair<double, double> Widget::caculate_oncircle(double x, double y) {
    double o_x = 1090;
    double o_y = 640;
    double next_y{};
    next_y = sqrt(68122 - pow((o_x - x - 1), 2)) + o_y;
    return {x + 1, next_y};
}

//调整小车速度,红绿灯时间间隔
void Widget::sleep(unsigned int msec) {

    QTime newTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < newTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void Widget::LightShow() {
    while(1) {

        // green
        light_status = 0;
        while(time_count) {
            ui->Green_Led->show();
            ui->Red_Led->hide();
            ui->Yellow_Led->hide();
            time_count--;
            sleep(500);
            ui->lcdNumber->display(time_count);
        }
        time_count = 3;
        ui->lcdNumber->display(time_count);

        // yellow
        light_status = 1;
        while(time_count) {
            ui->Green_Led->hide();
            ui->Red_Led->hide();
            ui->Yellow_Led->show();
            time_count--;
            sleep(500);
            ui->lcdNumber->display(time_count);
        }
        time_count = 10;
        ui->lcdNumber->display(time_count);

        // red
        light_status = 2;
        while(time_count) {
        ui->Green_Led->hide();
        ui->Red_Led->show();
        ui->Yellow_Led->hide();
        time_count--;
        sleep(500);
        ui->lcdNumber->display(time_count);
        }
        time_count = 15;
        ui->lcdNumber->display(time_count);
    }
}

