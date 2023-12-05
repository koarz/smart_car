#include "carthread.h"

#include <QTime>

CarThread::CarThread(QObject *parent) :QThread(parent) {}
void CarThread::run() {
    for (int i = car1->y(); i<600; i++) {
        car1->setGeometry(car1->x(),i,
                                 car1->width()
                                 ,car1->height());

    }
}

//void CarThread::sleep(unsigned int msec){

//    QTime newTime = QTime::currentTime().addMSecs(msec);
//    while(QTime::currentTime() < newTime)
//         QCoreApplication::processEvents(QEventLoop::AllEvents,100);
//}
