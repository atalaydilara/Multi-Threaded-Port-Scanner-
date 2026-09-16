#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scannerthread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();

    void acikPortGoster(int port);
    void progressGoster(int value);
    void durumYaz(QString mesaj);
    void taramaBittiSlot();

private:
    Ui::MainWindow *ui;
    ScannerThread *threadim;
};

#endif // MAINWINDOW_H
