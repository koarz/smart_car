#ifndef CARTHREAD_H
#define CARTHREAD_H

#include <QObject>
#include <QThread>
#include <QLabel>

class CarThread : public QThread
{
    Q_OBJECT
public:
    explicit CarThread(QObject *parent = nullptr);
    QLabel *car1;
//    void sleep(unsigned int msec);

protected:
    void run();

signals:

public slots:

};

#endif // CARTHREAD_H
