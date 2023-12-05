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

}

//start按钮点击事件
void Widget::on_pushButton_clicked()
{
    run1();
    LightShow();
}

//小车混流行驶
void Widget::run1() {
    //设定小车行走路线
    for(int i = ui->label_2->y();i<600;i++){
        ui->label_2->setGeometry(ui->label_2->x(),i,
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(5);
    }


    for (int i = ui->label_2->x();i < 550; i++) {
        ui->label_2->setGeometry(i,ui->label_2->y(),
                                 ui->label_2->width()
                                 ,ui->label_2->height());
        sleep(5);
    }
}

//调整小车速度
void Widget::sleep(unsigned int msec) {

    QTime newTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < newTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

void Widget::LightTime() {


    ui->lcdNumber->display(time_count);
    LightShow();
}



void Widget::LightShow() {
    while(1) {

        if (green_flag) {
            while(time_count) {
                ui->Green_Led->show();
                ui->Red_Led->hide();
                ui->Yellow_Led->hide();

                time_count--;
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
                ui->lcdNumber->display(time_count);
            }
            green_flag = true;
            time_count = 10;
            ui->lcdNumber->display(time_count);
            red_flag = false;

        }
    }
}


