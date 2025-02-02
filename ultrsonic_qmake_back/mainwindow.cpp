#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    serial->setPortName("/dev/ttyACM0");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
        qDebug() << "Serial port opened successfully.";
    } else {
        qDebug() << "Error opening serial port: " << serial->errorString();
    }
}

MainWindow::~MainWindow()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete ui;
}

void MainWindow::readSerial()
{
    QByteArray data = serial->readAll();
    serialData += QString::fromStdString(data.toStdString());

    while (serialData.contains("\r\n")) {
        int index = serialData.indexOf("\r\n");
        QString line = serialData.left(index);
        serialData.remove(0, index + 2);

        bool ok;
        int distance = line.toInt(&ok);
        if (ok) {
            updateGauge(distance);
            updateLine(distance);
        }
    }
}

void MainWindow::updateGauge(int value)
{
    ui->lcdNumber->display(value);
}

void MainWindow::updateLine(int value)
{
    if (value <= 10) {
        ui->line->setStyleSheet("border-left: 10px solid red; border-right: 10px solid red; border-top: 10px solid red; border-bottom: none;");
    } else {
        ui->line->setStyleSheet("border-left: 10px solid gray; border-right: 10px solid gray; border-top: 10px solid gray; border-bottom: none;");
    }
}
