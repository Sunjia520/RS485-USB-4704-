#include "mythread.h"
#include <iostream>
#include <QString>

MyThread::MyThread(QObject *parent):
    QThread(parent)
{

}

void MyThread::run(){
    while(!read_status){
        emit read_out();
        sleep(1);
    }
    while(!send_status){
        emit send_out();
        msleep(100);
    }

    if(send_status){
        emit arc_on();
    }

    msleep(1200);
    while(send_status&&read_status&&!fire_status){
        emit read_out();
        msleep(1200);
    }
    if(send_status&&fire_status){
        emit arc_off();
    }


}

void MyThread::stop_read(){
    read_status=true;
}

void MyThread::stop_send(){
    send_status=true;
}

void MyThread::fire_off(){
    fire_status=true;
}

void MyThread::maintain_arc_stop(){
    read_status=false;
}

void MyThread::init(){
    read_status=false;
    send_status=false;
    fire_status=false;
}
