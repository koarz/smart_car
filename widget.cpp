#include "widget.h"
#include "ui_widget.h"


#include <QTime>





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
//    ui->barrier_car->hide();

}

//start按钮点击事件
void Widget::on_pushButton_clicked()
{
    if (buttonIsClinked) {
        return;
    } else {
        buttonIsClinked = true;
    }

    run1();
    LightShow();
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
            ui->label_2->setGeometry(ui->label_2->x() + 1, ui->label_2->y(),
                                     ui->label_2->width()
                                     ,ui->label_2->height());

            QMatrix matrix;
            matrix.rotate((i - 500) * -0.6);                   //实现左转
            QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
            ui->label_2->setPixmap(pix);

        }
    }

    ui->barrier_car->show();

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
                QMatrix matrix;
                matrix.rotate(-90 + (i - 300) * -0.225);                      //向左变道
                QPixmap pix = QPixmap(":/images/car.png").transformed(matrix, Qt::SmoothTransformation);
                ui->label_2->setPixmap(pix);
                ui->label_2->setGeometry(i, ui->label_2->y() - 0.00001,
                                         ui->label_2->width()
                                         ,ui->label_2->height());
            } else {
                QMatrix matrix;
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

void Widget::updateposition(int i,int x,int y,int width, int height) //小车的位置更新
{
    if(i==1)  ui->label_2->setGeometry(x,y,width,height); //车 1 的位置更新
    if(i==2)  ui->barrier_car->setGeometry(x,y,width,height); //车 2 的位置更新
//    if(i==3)  ui->person->setGeometry(x,y,width,height); //person 的位置更新
}


