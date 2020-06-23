#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QIODevice>
#include <QVector>
#include <QByteArray>
#include <QMessageBox>
#include <QButtonGroup>
#include <QMainWindow>
#include <regex>
#include <direct.h>
#include <QDialog>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QMessageBox>
#include <QTreeWidget>
#include <QFileDialog>
#include <vector>
#include <QtCharts>
#include <QTimer>
#include <math.h>
#include <memory>
#include <QtCore>
#include <QtNetwork>
#include "mythread.h"

#include "controlthread.h"

using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct{
    char send_data[5];
    QByteArray recive_data;
} Send_Recive_Data;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signal_24_data();
    void signal_4_data();

    void stop_read();
    void stop_send();

    void initThread();
    void fire_off();

    void maintain_arc_off();

//TCP 客户端使用的槽函数
public slots:
    void ReadError(QAbstractSocket::SocketError);
    void on_pushConnect_clicked();

    void sendIO();

    void readIO();

private slots:
    void on_checkButton_clicked();
    void read_port();
    void parse_24_data();
    void parse_4_data();

    void on_connectButton_clicked();

    void on_disconnectButton_clicked();


    void on_weldstatepushButton_clicked();

    //void on_powder_checkBox_stateChanged(int arg1);

    void on_powder_checkBox_clicked();

   // void on_maintan_arc_checkBox_clicked();
    void on_maintan_arc_checkBox_clicked(bool checked);

    void on_mainarc_checkBox_clicked();

    void on_reflash_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_powder_state_clicked();

    void on_current_pushButton_clicked();

    void on_weldtime_pushButton_clicked();

    void on_internaltime_pushButton_clicked();

    void on_updowntime_pushButton_clicked();

    void on_gastime_pushButton_clicked();

    void on_motospeed_pushButton_clicked();

    void on_send_powder_delay_pushButton_clicked();

    void on_gas_check_pushButton_clicked();

    //采集页面槽函数
    void ReceiveAnalogData(QVector<double>);

    void on_data_collect_initial_pushButton_clicked();

    void on_data_collect_start_pushButton_clicked();

    void on_data_collect_stop_pushButton_clicked();

    void on_data_collect_save_pushButton_clicked();

    void on_BrowserBtn_3_clicked();

    //TCP 客户端的槽函数
    void on_servo_on_off_clicked(bool checked);

    void on_get_cur_job_clicked();

    void on_start_cur_job_clicked();

    void on_set_cur_job_clicked();

    void on_cur_mode_clicked();

    void recv_response();




private:
    Ui::MainWindow *ui;
    QSerialPort* mycom_port;
    Send_Recive_Data * my_exchange_data;
    QButtonGroup* state_box, *current_box, *time_box,*powder_box,*powder_state_box,*gas_check_box;



    void search_port_add_combox();
    void get_fullinfo_from_slave();
    void parse_data();
    void set_double_time_helper(double time);
    void set_int_time_helper(int time);

    QString mSavePath;

    std::string g_SaveFolder;

    QLineSeries* i_series;
    QChart* i_chart;
    QValueAxis* i_axisX;
    QValueAxis* i_axisY;

    QLineSeries* v_series;
    QChart* v_chart;
    QValueAxis* v_axisX;
    QValueAxis* v_axisY;
    ControlThread* mpControlThread = nullptr;

    //TCP客户端的变量
    QTcpSocket * tcpClient;
    QTimer tm;
    QStringList list;
    QString sActiveCmd;
    QString recvStr;
    void closeEvent(QCloseEvent *);

    MyThread* thread;

    volatile bool read_first=false;

    bool arc_status=true;

};
#endif // MAINWINDOW_H
