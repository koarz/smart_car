#include "widget.h"
#include "ui_widget.h"

#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QGraphicsRotation>
#include <QThread>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
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

}

//start按钮点击事件
void Widget::on_pushButton_clicked()
{
    connect(this, &Widget::startRun1, this, &Widget::onRun1Finished);
    connect(this, &Widget::startLightShow, this, &Widget::onLightShowFinished);

    QThread* run1Thread = new QThread;
    QThread* lightShowThread = new QThread;

    moveToThread(run1Thread);
    moveToThread(lightShowThread);

    connect(run1Thread, &QThread::started, this, &Widget::run1);
    connect(lightShowThread, &QThread::started, this, &Widget::LightShow);

    connect(run1Thread, &QThread::finished, run1Thread, &QThread::deleteLater);
    connect(lightShowThread, &QThread::finished, lightShowThread, &QThread::deleteLater);

    run1Thread->start();
    lightShowThread->start();

    emit startRun1();
    emit startLightShow();
//-------------------------------------------------------------------------------------------------


}

//小车混流行驶
void Widget::run1() {
    //设定小车行走路线
    for(int i = ui->label_2->y(); i < 600; i++){
        ui->label_2->setGeometry(ui->label_2->x(),i,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        if (i < 400) {
            sleep(10);
        } else {
            sleep(20);
            ui->label_2->setGeometry(ui->label_2->x() + 1, ui->label_2->y(),
                                     ui->label_2->width()
                                     ,ui->label_2->height());

            QTransform matrix;
            matrix.rotate((i - 400) * -0.45);                   //实现左转
            QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
            ui->label_2->setPixmap(pix);

        }
    }

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
        ui->label_2->setGeometry(i,ui->label_2->y(),
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(10);
    }

}

//调整小车速度,红绿灯时间间隔
void Widget::sleep(unsigned int msec) {

    QTime newTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < newTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void Widget::LightShow() {
    while(1) {
        if (green_flag) {
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
            green_flag = false;
            yellow_flag = true;

        }

        if (yellow_flag) {
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
            yellow_flag = false;
            red_flag = true;

        }

        if (red_flag) {
            while(time_count) {
                ui->Green_Led->hide();
                ui->Red_Led->show();
                ui->Yellow_Led->hide();
                time_count--;
                sleep(500);
                ui->lcdNumber->display(time_count);
            }
            green_flag = true;
            time_count = 10;
            ui->lcdNumber->display(time_count);
            red_flag = false;
        }
    }
}

void Widget::onRun1Finished()
{
    // 你可以在这里添加在 run1 完成后的任何后续处理代码。
    // 例如，重新启用用户界面元素、更新状态等。
    // 如果你不需要添加特定的内容，可以将其保留为空。
//    QMetaObject::invokeMethod(this, "updateUIAfterRun1", Qt::QueuedConnection);
}

void Widget::onLightShowFinished()
{
//    // 你可以在这里添加在 LightShow 完成后的任何后续处理代码。
//    // 例如，重新启用用户界面元素、更新状态等。
//    // 如果你不需要添加特定的内容，可以将其保留为空。
//    QMetaObject::invokeMethod(this, "updateUIAfterLightShow", Qt::QueuedConnection);
}

