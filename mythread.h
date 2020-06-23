#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QTime>

class MyThread:public QThread
{
    Q_OBJECT
public:
    MyThread(QObject *parent=nullptr);
    void run();
    //void setStr(QString* str);

signals:
    void read_out();
    void send_out();
    void arc_on();
    void arc_off();


private slots:
    void stop_read();
    void stop_send();
    void fire_off();
    void init();
    void maintain_arc_stop();

private:
    volatile bool read_status=false;
    volatile bool send_status=false;
    volatile bool fire_status=false;
    //QString* str;
    //int num=0;

};

#endif // MYTHREAD_H
