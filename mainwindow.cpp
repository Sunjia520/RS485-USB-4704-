#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMetaType>
#include <memory>

Q_DECLARE_METATYPE(QVector<double>);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,mycom_port(new QSerialPort)
    ,my_exchange_data(new Send_Recive_Data)
    ,state_box(new QButtonGroup)
    ,current_box(new QButtonGroup)
    ,time_box(new QButtonGroup)
    ,powder_box(new QButtonGroup)
    ,powder_state_box(new QButtonGroup)
    ,gas_check_box(new QButtonGroup)
{
    ui->setupUi(this);
    setWindowTitle("焊机通讯和数据采集");
    ui->disconnectButton->setEnabled(false);
    //检查串口，添加到combox
    search_port_add_combox();
    my_exchange_data->send_data[0] = 0x0f; //设置地址码

    state_box->addButton(ui->pulseweldradioButton, 0);
    state_box->addButton(ui->continueweldradioButton,1);

    current_box->addButton(ui->weldcurrent_radioButton,0);
    current_box->addButton(ui->basecurrent_radioButton, 1);
    current_box->addButton(ui->maintiancurrent_radioButton, 2);

    time_box->addButton(ui->weld_time_radiobutton, 0);
    time_box->addButton(ui->intelvaltime_radioButton, 1);
    time_box->addButton(ui->gas_delay_radioButton, 2);
    time_box->addButton(ui->uptime_radioButton, 3);
    time_box->addButton(ui->down_time_radioButton, 4);
    time_box->addButton(ui->protect_gas_radioButton, 5);

    powder_box->addButton(ui->manual_send_powder_radioButton,0);
    powder_box->addButton(ui->auto_send_powder_radioButton,1);

    powder_state_box->addButton(ui->motorspeed_radiobutton,0);
    powder_state_box->addButton(ui->sendpowderdelay_radioButton,1);
    powder_state_box->addButton(ui->send_powder_delay_end_radioButton,2);

    gas_check_box->addButton(ui->gas_check_end_radioButton,0);
    gas_check_box->addButton(ui->send_powder_gas_radioButton,1);
    gas_check_box->addButton(ui->ionic_gas_radioButton,2);
    gas_check_box->addButton(ui->protect_gas_radioButton_2,3);

    ui->gas_check_end_radioButton->setEnabled(false);
    ui->send_powder_gas_radioButton->setEnabled(false);
    ui->ionic_gas_radioButton->setEnabled(false);
    ui->protect_gas_radioButton_2->setEnabled(false);

    ui->motorspeed_radiobutton->setEnabled(false);
    ui->sendpowderdelay_radioButton->setEnabled(false);
    ui->send_powder_delay_end_radioButton->setEnabled(false);

    ui->manual_send_powder_radioButton->setEnabled(false);
    ui->auto_send_powder_radioButton->setEnabled(false);

    ui->weld_time_radiobutton->setEnabled(false);
    ui->uptime_radioButton->setEnabled(false);
    ui->down_time_radioButton->setEnabled(false);
    ui->gas_delay_radioButton->setEnabled(false);
    ui->intelvaltime_radioButton->setEnabled(false);
    ui->protect_gas_radioButton->setEnabled(false);


    ui->basecurrent_radioButton->setEnabled(false);
    ui->maintiancurrent_radioButton->setEnabled(false);
    ui->weldcurrent_radioButton->setEnabled(false);
    ui->pulseweldradioButton->setEnabled(false);
    ui->continueweldradioButton->setEnabled(false);

    ui->current_spinBox->setRange(2,300);
    ui->weld_time_spinBox->setRange(0,999);
    ui->internal_time_spinBox->setRange(0,999);
    ui->internal_time_spinBox->setSingleStep(10);
    ui->up_down_time_doubleSpinBox->setRange(0.0,5.0);
    ui->up_down_time_doubleSpinBox->setSingleStep(0.1);
    ui->gas_time_spinBox->setRange(1,20);
    ui->motospeed_spinBox->setRange(1,100);
    ui->send_powder_delay_spinBox->setRange(-5,5);

    ui->current_diaplay->setPalette(Qt::green);
    ui->timedisplay->setPalette(Qt::green);
    ui->senpowder_value_display->setPalette(Qt::green);


    ui->weldcurrent_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->basecurrent_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );

    ui->maintiancurrent_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );

    ui->pulseweldradioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->continueweldradioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->weld_time_radiobutton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->intelvaltime_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->uptime_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->down_time_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->gas_delay_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->protect_gas_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->manual_send_powder_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->auto_send_powder_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->send_powder_delay_end_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->sendpowderdelay_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->motorspeed_radiobutton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->gas_check_end_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->send_powder_gas_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->ionic_gas_radioButton->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );
    ui->protect_gas_radioButton_2->setStyleSheet("QRadioButton::indicator {width:15px;height:15px;border-radius:7px}"
                                   "QRadioButton::indicator:checked {background-color:green;}"
                                   "QRadioButton::indicator:unchecked {background-color:white;}"
                                   );

    ui->mainarc_checkBox->setStyleSheet(
         "QCheckBox::indicator {width: 15px; height:15px;}"
          "QCheckBox::indicator:unchecked {background-color:white;}"
          "QCheckBox::indicator:checked {background-color:green;}");
    ui->maintan_arc_checkBox->setStyleSheet(
         "QCheckBox::indicator {width: 15px; height:15px;}"
          "QCheckBox::indicator:unchecked {background-color:white;}"
          "QCheckBox::indicator:checked {background-color:green;}");
    ui->powder_checkBox->setStyleSheet(
         "QCheckBox::indicator {width: 15px; height:15px;}"
          "QCheckBox::indicator:unchecked {background-color:white;}"
          "QCheckBox::indicator:checked {background-color:green;}");


    connect(mycom_port,SIGNAL(readyRead()),this,SLOT(read_port()));
    connect(this, SIGNAL(signal_24_data()), this, SLOT(parse_24_data()));
    connect(this, SIGNAL(signal_4_data()), this , SLOT(parse_4_data()));

    //采集页面初始化
    qRegisterMetaType<QVector<double>>("QVector<double>");

        i_series = new QLineSeries;
        i_series->setUseOpenGL(true);
        i_chart = new QChart;
        i_series->append(0, 0);
        i_chart->addSeries(i_series);
        i_chart->createDefaultAxes();

        i_axisX =new QValueAxis;
        i_axisX->setRange(0, 60);
        i_axisX->setGridLineVisible(true);
        i_axisX->setTickCount(7);     //标记的个数
        i_axisX->setMinorTickCount(1); //次标记的个数

        i_axisY = new QValueAxis;
        i_axisY->setRange(50, 300);
        i_axisY->setGridLineVisible(true);
        i_axisY->setTickCount(6);
        //i_axisY->setMinorTickCount(1);

        i_chart->setAxisX(i_axisX, i_series);
        i_chart->setAxisY(i_axisY, i_series);
        i_chart->setTitle("Current");
        i_chart->legend()->hide();
        i_chart->setMargins(QMargins(0, 0, 0, 0));
        i_chart->setTheme(QChart::ChartThemeDark);

        v_series = new QLineSeries;
        v_series->setUseOpenGL(true);
        v_chart = new QChart;
        v_series->append(0, 0);
        v_chart->addSeries(v_series);
        v_chart->createDefaultAxes();

        v_axisX = new QValueAxis;
        v_axisX->setRange(0, 60);
        v_axisX->setGridLineVisible(true);
        v_axisX->setTickCount(7);     //标记的个数
        v_axisX->setMinorTickCount(1); //次标记的个数

        v_axisY = new QValueAxis;
        v_axisY->setRange(0, 30);
        v_axisY->setGridLineVisible(true);
        v_axisY->setTickCount(5);
            //v_axisY->setMinorTickCount(1);

        v_chart->setAxisX(v_axisX, v_series);
        v_chart->setAxisY(v_axisY, v_series);
        v_chart->setTitle("Voltage");
        v_chart->legend()->hide();
        v_chart->setMargins(QMargins(0, 0, 0, 0));
        v_chart->setTheme(QChart::ChartThemeDark);

        ui->graphicsView_2->setChart(i_chart);
        ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

        ui->graphicsView_3->setChart(v_chart);
        ui->graphicsView_3->setRenderHint(QPainter::Antialiasing);

        ui->AI_Current->setPalette(Qt::green);
        ui->AI_Voltage->setPalette(Qt::green);

        ui->data_collect_initial_pushButton->setEnabled(true);
        ui->data_collect_save_pushButton->setEnabled(false);
        ui->data_collect_stop_pushButton->setEnabled(false);
        ui->data_collect_start_pushButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mycom_port;
    delete my_exchange_data;
}

void MainWindow::search_port_add_combox(){
    QList<QSerialPortInfo> Port_List = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& port_info:Port_List){
        QSerialPort serial;
        serial.setPort(port_info);
        if(serial.open(QIODevice::ReadWrite)){
            ui->comport_combox->addItem(port_info.portName());
            serial.close();
        }
    }
}


void MainWindow::on_checkButton_clicked()
{
    ui->comport_combox->clear();
    search_port_add_combox();
}

void MainWindow::on_connectButton_clicked()
{
    if(ui->comport_combox->currentText().isEmpty()) return;
    if(mycom_port == nullptr || mycom_port->isOpen()) return;
    //设置信息

    mycom_port->setPortName(ui->comport_combox->currentText());
    mycom_port->setBaudRate(QSerialPort::Baud9600);
    mycom_port->setDataBits(QSerialPort::Data8);
    mycom_port->setParity(QSerialPort::OddParity);
    mycom_port->setStopBits(QSerialPort::OneStop);
    mycom_port->setFlowControl(QSerialPort::NoFlowControl);
    if(!mycom_port->open(QSerialPort::ReadWrite)){
        QMessageBox::warning(this, tr("WARNING"), tr("串口打开失败"), QMessageBox::Ok);
        return;
    }
    ui->disconnectButton->setEnabled(true);
    ui->connectButton->setEnabled(false);
    get_fullinfo_from_slave();
}

void MainWindow::read_port(){
    my_exchange_data->recive_data.append(mycom_port->readAll());
    //std::cout << my_exchange_data->recive_data.size() << std::endl;
    if(my_exchange_data->recive_data.size()>4){
        if(my_exchange_data->recive_data.size()==24) emit signal_24_data();
    }
    else if(my_exchange_data->recive_data.size() == 4){
        if(my_exchange_data->recive_data.at(1) != 0x0e) emit signal_4_data();
    }
}

void MainWindow::get_fullinfo_from_slave(){
    this->my_exchange_data->send_data[1] = 0x0e;
    this->my_exchange_data->send_data[2] = 0x00;
    this->my_exchange_data->send_data[3] = 0x00;
    this->my_exchange_data->send_data[4] = 0x1d;
    mycom_port->write(my_exchange_data->send_data, 5);
    //std::cout << mycom_port->readAll().size() << std::endl;


    //parse_data();
}

void MainWindow::parse_24_data(){
    parse_data();
}

void MainWindow::parse_4_data(){

}

void MainWindow::parse_data(){
    //焊接状态
    switch (my_exchange_data->recive_data.at(2)) {
    case 0x00:
        ui->pulseweldradioButton->setChecked(true);
        break;
    case 0x01:
        ui->continueweldradioButton->setChecked(true);
        break;
    }
    //ui->weld_state_combox->setCurrentIndex(==0x00? 0:1);
    //维弧开关
    ui->maintan_arc_checkBox->setCheckState(my_exchange_data->recive_data.at(3)==0x01? Qt::Checked:Qt::Unchecked);
    //气体检测
    switch (my_exchange_data->recive_data.at(4)) {
    case 0x00:
        ui->gas_check_end_radioButton->setChecked(true);
        break;
    case 0x01:
        ui->send_powder_gas_radioButton->setChecked(true);
        break;
    case 0x02:
        ui->ionic_gas_radioButton->setChecked(true);
        break;
    case 0x03:
        ui->protect_gas_radioButton_2->setChecked(true);
        break;
    }
    //送粉方式
    switch (my_exchange_data->recive_data.at(5)) {
    case 0x00:
        ui->manual_send_powder_radioButton->setChecked(true);
        ui->powder_checkBox->setEnabled(true);
        break;
    case 0x01:
        ui->auto_send_powder_radioButton->setChecked(true);
        ui->powder_checkBox->setEnabled(false);
        break;
    }
    //送粉开关
    ui->powder_checkBox->setCheckState(my_exchange_data->recive_data.at(6)==0x01? Qt::Checked:Qt::Unchecked);
    //电流
    switch (my_exchange_data->recive_data.at(7)) {
        case 0x00:
        ui->weldcurrent_radioButton->setChecked(true);
        ui->current_diaplay->display((*(my_exchange_data->recive_data.constData()+11)<<8 | *(my_exchange_data->recive_data.constData()+12)));
        break;
        case 0x01:
        ui->basecurrent_radioButton->setChecked(true);
        ui->current_diaplay->display((*(my_exchange_data->recive_data.constData()+13)<<8 | *(my_exchange_data->recive_data.constData()+14)));
        break;
        case 0x02:
        ui->maintiancurrent_radioButton->setChecked(true);
        ui->current_diaplay->display(qvariant_cast<quint8>(*(my_exchange_data->recive_data.constData()+15)));
        break;
    }
    //时间
    switch (my_exchange_data->recive_data.at(8)) {
    case 0x00:
        ui->weld_time_radiobutton->setChecked(true);
        ui->timedisplay->display((*(my_exchange_data->recive_data.constData()+16)<<8 | *(my_exchange_data->recive_data.constData()+17)));
        break;
    case 0x01:
        ui->intelvaltime_radioButton->setChecked(true);
        ui->timedisplay->display(qvariant_cast<quint8>(*(my_exchange_data->recive_data.constData()+18)));
        break;
    case 0x02:
        ui->gas_delay_radioButton->setChecked(true);
        ui->timedisplay->display(qvariant_cast<quint8>(*(my_exchange_data->recive_data.constData()+19)));
        break;
    case 0x03:
        ui->uptime_radioButton->setChecked(true);
        ui->timedisplay->display(qvariant_cast<double>(*(my_exchange_data->recive_data.constData()+20))/10);
        break;
    case 0x04:
        ui->down_time_radioButton->setChecked(true);
        ui->timedisplay->display(qvariant_cast<double>(*(my_exchange_data->recive_data.constData()+21))/10);
        break;
    }
    //送粉状态
    switch (my_exchange_data->recive_data.at(9)) {
    case 0x00:
        ui->motorspeed_radiobutton->setChecked(true);
        ui->senpowder_value_display->display(qvariant_cast<quint8>(*(my_exchange_data->recive_data.constData()+22)));
        break;
    case 0x01:
        ui->sendpowderdelay_radioButton->setChecked(true);
        ui->senpowder_value_display->display(qvariant_cast<quint8>(*(my_exchange_data->recive_data.constData()+23))-6);
        break;
    }
    //主弧开关
    ui->mainarc_checkBox->setCheckState(my_exchange_data->recive_data.at(6)==0x01? Qt::Checked:Qt::Unchecked);
}

void MainWindow::on_disconnectButton_clicked()
{
    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    my_exchange_data->recive_data.clear();
    mycom_port->clear();
    mycom_port->close();
}


/*void MainWindow::on_weld_state_combox_currentIndexChanged(int index)
{
    my_exchange_data->send_data[1] = 0x02;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x11;
    //my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
}*/

void MainWindow::on_weldstatepushButton_clicked()
{
    my_exchange_data->send_data[1] = 0x02;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x11;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
    int id = state_box->checkedId();
    if(id == -1) return;
    if(id == 0){
        ui->continueweldradioButton->setChecked(true);
    }else {
       ui->pulseweldradioButton->setChecked(true);
    }
}


void MainWindow::on_powder_checkBox_clicked()
{
    my_exchange_data->send_data[1] = 0x06;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x15;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
}

void MainWindow::on_maintan_arc_checkBox_clicked()
{
    my_exchange_data->send_data[1] = 0x03;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x12;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
}

void MainWindow::on_mainarc_checkBox_clicked()
{
    my_exchange_data->send_data[1] = 0x0a;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x19;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
}

void MainWindow::on_reflash_clicked()
{
    my_exchange_data->recive_data.clear();
    get_fullinfo_from_slave();
}

void MainWindow::on_pushButton_6_clicked()
{
    my_exchange_data->send_data[1] = 0x07;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x16;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
    int id = current_box->checkedId();
    QRadioButton* button = (QRadioButton*)(current_box->button((id+1)%3));
    button->setChecked(true);
}

void MainWindow::on_pushButton_5_clicked()
{
    my_exchange_data->send_data[1] = 0x08;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x17;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
    int id = time_box->checkedId();
    QRadioButton* button = (QRadioButton*)(time_box->button((id+1)%6));
    button->setChecked(true);
}


void MainWindow::on_pushButton_4_clicked()
{
    my_exchange_data->send_data[1] = 0x05;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x14;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
    int id = powder_box->checkedId();
    if(id==0)
        ui->powder_checkBox->setEnabled(false);
    else {
       ui->powder_checkBox->setEnabled(true);
    }
    QRadioButton* button = (QRadioButton*)(powder_box->button((id+1)%2));
    button->setChecked(true);
}

void MainWindow::on_powder_state_clicked()
{
    my_exchange_data->send_data[1] = 0x09;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x18;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
    int id = powder_state_box->checkedId();
    QRadioButton* button = (QRadioButton*)(powder_state_box->button((id+1)%3));
    button->setChecked(true);
}


void MainWindow::on_current_pushButton_clicked()
{
    int curr=ui->current_spinBox->text().toInt();

     my_exchange_data->send_data[1] = 0x0b;
     my_exchange_data->send_data[2] = 0x00;
     my_exchange_data->send_data[3] = 0x00+curr;
     my_exchange_data->send_data[4] = 0x1a+curr;
     my_exchange_data->recive_data.clear();
     mycom_port->write(my_exchange_data->send_data, 5);

     ui->current_diaplay->display(curr);

}

void MainWindow::set_int_time_helper(int time)
{
    int lo=time%256;
    int hi=time/256;

     my_exchange_data->send_data[1] = 0x0c;
     my_exchange_data->send_data[2] = 0x00+hi;
     my_exchange_data->send_data[3] = 0x00+lo;
     my_exchange_data->send_data[4] = 0x1b+time;
     my_exchange_data->recive_data.clear();
     mycom_port->write(my_exchange_data->send_data, 5);

     ui->timedisplay->display(time);

}

void MainWindow::set_double_time_helper(double time)
{
    int temp=time*10;

     my_exchange_data->send_data[1] = 0x0c;
     my_exchange_data->send_data[2] = 0x00;
     my_exchange_data->send_data[3] = 0x00+temp;
     my_exchange_data->send_data[4] = 0x1b+temp;
     my_exchange_data->recive_data.clear();
     mycom_port->write(my_exchange_data->send_data, 5);

     ui->timedisplay->display(time);

}


void MainWindow::on_weldtime_pushButton_clicked()
{
    int time=ui->weld_time_spinBox->text().toInt();
    set_int_time_helper(time);
}

void MainWindow::on_internaltime_pushButton_clicked()
{
    int time=ui->internal_time_spinBox->text().toInt();
    time/=10;
    int lo=time%256;
    int hi=time/256;

     my_exchange_data->send_data[1] = 0x0c;
     my_exchange_data->send_data[2] = 0x00+hi;
     my_exchange_data->send_data[3] = 0x00+lo;
     my_exchange_data->send_data[4] = 0x1b+time;
     my_exchange_data->recive_data.clear();
     mycom_port->write(my_exchange_data->send_data, 5);

     ui->timedisplay->display(time*10);
}

void MainWindow::on_updowntime_pushButton_clicked()
{
    double time=ui->up_down_time_doubleSpinBox->text().toDouble();
    set_double_time_helper(time);
}



void MainWindow::on_gastime_pushButton_clicked()
{
    int time=ui->gas_time_spinBox->text().toInt();
    set_int_time_helper(time);
}

void MainWindow::on_motospeed_pushButton_clicked()
{
    int num=ui->motospeed_spinBox->text().toInt();
    my_exchange_data->send_data[1] = 0x0d;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00+num;
    my_exchange_data->send_data[4] = 0x1c+num;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);

    ui->senpowder_value_display->display(num);
}


void MainWindow::on_send_powder_delay_pushButton_clicked()
{
    int num=ui->send_powder_delay_spinBox->text().toInt();

    num+=6;
    my_exchange_data->send_data[1] = 0x0d;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00+num;
    my_exchange_data->send_data[4] = 0x1c+num;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);

    ui->senpowder_value_display->display(num-6);
}

void MainWindow::on_gas_check_pushButton_clicked()
{
    my_exchange_data->send_data[1] = 0x04;
    my_exchange_data->send_data[2] = 0x00;
    my_exchange_data->send_data[3] = 0x00;
    my_exchange_data->send_data[4] = 0x13;
    my_exchange_data->recive_data.clear();
    mycom_port->write(my_exchange_data->send_data, 5);
    int id = gas_check_box->checkedId();
    QRadioButton* button = (QRadioButton*)(gas_check_box->button((id+1)%4));
    button->setChecked(true);
}

void MainWindow::on_data_collect_initial_pushButton_clicked()
{
    mpControlThread = new ControlThread();
    int rtn = mpControlThread->Initialize();
    if (rtn != 0)
    {
       QMessageBox::warning(this, tr("Warning"), tr(("未连接到数据采集板")), QMessageBox::Ok);
        return;
    }
    else
    {
        QMessageBox::information(this, tr("Information"), mpControlThread->GetDeviceName()+tr(" 已连接"), QMessageBox::Ok);
    }
    connect(mpControlThread, SIGNAL(SendAnalogData(QVector<double>)), this, SLOT(ReceiveAnalogData(QVector<double>)));
    ui->data_collect_save_pushButton->setEnabled(true);
    //ui->data_collect_stop_pushButton->setEnabled(true);
    ui->data_collect_start_pushButton->setEnabled(true);
}



void MainWindow::on_data_collect_start_pushButton_clicked()
{
    if (mpControlThread != nullptr && !mpControlThread->IsCollecting())
        {
            i_series->clear();
            v_series->clear();
            mpControlThread->StartCollect();
            ui->data_collect_stop_pushButton->setEnabled(true);
            ui->data_collect_start_pushButton->setEnabled(false);
        }
}



void MainWindow::on_data_collect_stop_pushButton_clicked()
{
    if (mpControlThread != nullptr && mpControlThread->IsCollecting()){
        mpControlThread->StopCollect();
        mpControlThread->StopSaving();
        ui->data_collect_start_pushButton->setEnabled(true);
        ui->data_collect_stop_pushButton->setEnabled(false);
        ui->data_collect_save_pushButton->setEnabled(true);

    }
}


void MainWindow::on_data_collect_save_pushButton_clicked()
{
    if(g_SaveFolder.size()>0){
        QMessageBox::information(this, tr("Information"), tr(" 已设置路径，开始保存！"), QMessageBox::Ok);
        time_t t = time(0);
        char tmp_time[64];
        strftime(tmp_time, sizeof(tmp_time), "%Y%m%d%H%M", localtime(&t));
        std::string savePath = g_SaveFolder + "\\" + std::string(tmp_time)+".csv";
        //mkdir(savePath.c_str());
        //mpControlThread->SetSavePath(savePath);
        mpControlThread->SetSavePath(savePath);
        mpControlThread->StartSaving();

        ui->data_collect_save_pushButton->setEnabled(false);
    }else{
        QMessageBox::warning(this, tr("Warning"), tr("请设置保存文件的路径"), QMessageBox::Ok);
        return;
    }
}

void MainWindow::on_BrowserBtn_3_clicked()
{
    mSavePath = QFileDialog::getExistingDirectory(this, tr("Save Path"), "D:/");
    std::cout<<mSavePath.size()<<std::endl;

    if (!mSavePath.isEmpty()) {

        ui->savepath_edit_3->setText(mSavePath);

        std::string tmp_dir = mSavePath.toStdString();
        tmp_dir = std::regex_replace(tmp_dir, std::regex("/"), std::string("\\"));
        g_SaveFolder = tmp_dir;
    }
}

void MainWindow::ReceiveAnalogData(QVector<double> analogData)
{
    int iCurrent = static_cast<int>(analogData[0] * 219);
    int iVoltage = static_cast<int>(analogData[1] * 21);
    double t = analogData[2];
    ui->AI_Current->display(iCurrent);
    ui->AI_Voltage->display(iVoltage);


    i_series->append(t, iCurrent);
    v_series->append(t, iVoltage);
}
