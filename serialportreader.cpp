#include "serialportreader.h"
#include <iomanip>      // std::setprecision
#include <QCoreApplication>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <stdio.h>

SerialPortReader::SerialPortReader(QSerialPort *serialPort, QObject *parent) :
    QObject(parent), //
    m_serialPort(serialPort),// m_serialPort is a function of QSerialPort and it takes the serialPort data
    m_standardOutput(stdout)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);//every time there is a signal on the serial port, this funcion runs
        //(it connects a signal to a slot)
}



double SerialPortReader::handleReadyRead()
{
    m_readData.append(m_serialPort->readAll()); //m_readData is an array of data from sensors
    double serial_reading=0.0;//it holds the data
    QString payload;//playload is a protocol parser, finds out the length of the piece of data

    if (pp.payload(&m_readData,&payload))//if there is anything in the playload 
    {
        serial_reading= payload.toDouble();//it gets the value of the playload (string) and it converts it into a double
        std::cout << " : " << serial_reading << std::endl; //it outputs on the screen
    }
    return serial_reading; //it returns the value that is outputed to use it elsewhere
}


