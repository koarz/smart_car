#ifndef WIDGET_H
#define WIDGET_H



#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QThread>

namespace Ui {
class Widget;
}



class Widget : public QWidget
{
    Q_OBJECT

public:

    class CarControl : public QThread{
    public:
        CarControl() = default;
        CarControl(Widget &widget) : widget(widget){};
        void run() override {
            widget.run1();
        }
    private:
        Widget &widget;
    };
    class Light : public QThread{
    public:
        Light() = default;
        Light(Widget &widget) : widget(widget){};
        void run() override {
            widget.LightShow();
        }
    private:
        Widget &widget;
    };
    explicit Widget(QWidget *parent = NULL);
    void LightShow();
    void Init();
    void updateposition(int ,int ,int ,int , int );
    ~Widget();

private slots:
    void on_pushButton_clicked(); //start按钮的槽函数
    void run1();        //小车混流行驶
    void run2();
    void sleep(unsigned int msec);//延时函数


signals:



private:
    CarControl car_control;
    Light light;
    Ui::Widget *ui;
    bool green_flag = true;
    bool yellow_flag = false;
    bool red_flag = false;
    int time_count = 10;
    bool buttonIsClinked = false;

};





#endif // WIDGET_H
