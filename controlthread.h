﻿#pragma once
#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include <bdaqctrl.h>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QVector>
#include <memory>

using namespace Automation::BDaq;

class ControlThread : public QObject
{
    Q_OBJECT

        class DataReadyHandler : public BfdAiEventListener
    {
    public:
        ControlThread * owner;
        virtual void BDAQCALL BfdAiEvent(void * sender, BfdAiEventArgs * args)
        {
            owner->DataHandler(sender, args);
        }
    };

    class OverrunHandler : public BfdAiEventListener
    {
    public:
        ControlThread * owner;
        virtual void BDAQCALL BfdAiEvent(void * sender, BfdAiEventArgs * args) {}
    };

    class CacheOverflowHandler : public BfdAiEventListener
    {
    public:
        ControlThread * owner;
        virtual void BDAQCALL BfdAiEvent(void * sender, BfdAiEventArgs * args) {}
    };

    class StoppedHandler : public BfdAiEventListener
    {
    public:
        ControlThread * owner;
        virtual void BDAQCALL BfdAiEvent(void * sender, BfdAiEventArgs * args) {}
    };

public:
    ControlThread();
    ~ControlThread();

    int Initialize();

    void SetSavePath(std::string& savePath);

    void StartCollect();
    void StopCollect();
    bool IsCollecting();
    void StartSaving();
    void StopSaving();
    QString GetDeviceName();

private:
    QString mDeviceName;
    BufferedAiCtrl* mpBufferedAiCtrl = nullptr;
    double *mpScaledData = nullptr;

    QFile mFile;
    QTextStream mTextStream;
    std::string mSavePath;
    QTime mTime;
    bool mIsCollecting;
    bool mIsSaving;

    QVector<double> mAnalogData;

    DataReadyHandler dataReadyHandler;
    OverrunHandler overrunHandler;
    CacheOverflowHandler cacheOverflowHandler;
    StoppedHandler stoppedHander;
    void DataHandler(void *sender, BfdAiEventArgs *args);

signals:
    void SendAnalogData(QVector<double>);
    void SendFinishSignal();
};

typedef std::shared_ptr<ControlThread> ControlThreadPtr;

#endif
