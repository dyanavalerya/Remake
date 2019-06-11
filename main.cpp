#include "dialog.h"
#include <QApplication>
#include "serialportreader.h"
#include <QApplication>
#include <QCoreApplication>
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //it's a class and it manages the UI settings (eg. startup, cosing), a is an instance of the class
    Dialog w;// a dialog window
    w.show();// function of Dialog class that opens the window
    QTextStream standardOutput(stdout);// serial communication, stdout - stream that c++ uses
    QSerialPort serialPort;// every time an usb is plugged in, it gives a unique product and vendor ID and name
    const QString serialPortName = "COM5";

    serialPort.setPortName(serialPortName); //set a port that we want to use
    serialPort.setBaudRate(9600);//the speed that the data is read or the communication rate (9600 bits/ second)

    if (!serialPort.open(QIODevice::ReadOnly)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")//%1 returns the port name, %2 the error name 
                          .arg(serialPortName)// inserts the name for %1
                          .arg(serialPort.errorString())//inserts the name for %2
                       << endl;

    }
    SerialPortReader serialPortReader(&serialPort);//it runs an instance of the SerialPortReader and it points to the serialPort address

    return a.exec();//runs the application a
}
