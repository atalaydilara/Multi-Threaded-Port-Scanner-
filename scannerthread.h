#ifndef SCANNERTHREAD_H
#define SCANNERTHREAD_H

#include <QThread>
#include <QString>

class ScannerThread : public QThread
{
    Q_OBJECT

public:
    explicit ScannerThread(QObject *parent = nullptr);

    void setValues(QString ipAdres, int baslangicPort, int bitisPort);
    void stopScan();

signals:
    void portAcik(int port);
    void progressGuncelle(int value);
    void durumGuncelle(QString mesaj);
    void taramaBitti();

protected:
    void run() override;

private:
    QString ip;
    int startPort;
    int endPort;
    bool durdur;
};

#endif // SCANNERTHREAD_H
