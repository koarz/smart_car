#ifndef WIDGET_H
#define WIDGET_H

#include "car.h"

#include <QWidget>
#include <QTimer>
#include <QObject>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = NULL);
    void LightTime();
    void LightShow();
    void TimeShow();
    void Init();
    ~Widget();

private slots:
    void on_pushButton_clicked(); //start按钮的槽函数
    void run1();                   //小车混流行驶
    void sleep(unsigned int msec);//延时函数




private:
    Ui::Widget *ui;
    bool green_flag = true;
    bool yellow_flag = false;
    bool red_flag = false;
    int time_count = 10;

};





#endif // WIDGET_H
