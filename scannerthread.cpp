#include "scannerthread.h"
#include <QTcpSocket>

ScannerThread::ScannerThread(QObject *parent)
    : QThread(parent)
{
    startPort = 1;
    endPort = 1024;
    durdur = false;
}

void ScannerThread::setValues(QString ipAdres, int baslangicPort, int bitisPort)
{
    ip = ipAdres;
    startPort = baslangicPort;
    endPort = bitisPort;
    durdur = false;
}

void ScannerThread::stopScan()
{
    durdur = true;
}

void ScannerThread::run()
{
    emit durumGuncelle("Scan started...");

    int toplamPort = endPort - startPort + 1;
    int sayac = 0;

    for(int port = startPort; port <= endPort; port++)
    {
        if(durdur == true)
        {
            emit durumGuncelle("Scan stopped");
            emit taramaBitti();
            return;
        }

        QTcpSocket socket;
        socket.connectToHost(ip, port);

        if(socket.waitForConnected(100))
        {
            emit portAcik(port);
            socket.disconnectFromHost();
        }

        sayac++;
        int yuzde = (sayac * 100) / toplamPort;
        emit progressGuncelle(yuzde);
    }

    emit durumGuncelle("Scan completed");
    emit taramaBitti();
}
