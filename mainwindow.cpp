#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadim = new ScannerThread(this);

    connect(threadim, SIGNAL(portAcik(int)), this, SLOT(acikPortGoster(int)));
    connect(threadim, SIGNAL(progressGuncelle(int)), this, SLOT(progressGoster(int)));
    connect(threadim, SIGNAL(durumGuncelle(QString)), this, SLOT(durumYaz(QString)));
    connect(threadim, SIGNAL(taramaBitti()), this, SLOT(taramaBittiSlot()));

    ui->progressBar->setValue(0);
    ui->label_status->setText("Ready");
}

MainWindow::~MainWindow()
{
    if(threadim->isRunning())
    {
        threadim->stopScan();
        threadim->wait();
    }

    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    int baslangic = ui->spinBox_startPort->value();
    int bitis = ui->spinBox_endPort->value();

    if(ip == "")
    {
       QMessageBox::warning(this, "Warning", "Please enter an IP address.");
        return;
    }

    if(baslangic > bitis)
    {
        QMessageBox::warning(this, "Warning", "Start port cannot be greater than end port.");
        return;
    }

    ui->listWidget_ports->clear();
    ui->progressBar->setValue(0);
    ui->label_status->setText("Scanning...");

    ui->pushButton_start->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);

    threadim->setValues(ip, baslangic, bitis);
    threadim->start();
}

void MainWindow::on_pushButton_stop_clicked()
{
    if(threadim->isRunning())
    {
        threadim->stopScan();
    }
}

void MainWindow::acikPortGoster(int port)
{
    ui->listWidget_ports->addItem("Port " + QString::number(port) + "  |  OPEN 🔓");
    ui->listWidget_ports->setCurrentRow(ui->listWidget_ports->count() - 1);
}

void MainWindow::progressGoster(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::durumYaz(QString mesaj)
{
    ui->label_status->setText(mesaj);
}

void MainWindow::taramaBittiSlot()
{
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
}
