#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "usbworker.h"
#include "welcomepage.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = new QThread(this);
    worker = new UsbWorker();
    flags = new bool[1]{false};
    // UsbWorker++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    connect(this, &MainWindow::destroyed, thread, &QThread::quit);
    connect(this, &MainWindow::signal_worker_wait_connection, worker, &UsbWorker::slot_wait);
    connect(worker, &UsbWorker::signal_flashDriveFound, this, &MainWindow::slot_worker_flashDriveFound);
    // UsbWorker----------------------------------------------------------------------------------------
    // WelcomePage++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    connect(ui->widget, SIGNAL(signal_pushButton_pressed()), this, SLOT(slot_wpage_button_pressed()));
    connect(this, SIGNAL(signal_wpage_restart()), ui->widget, SLOT(slot_restart()));
    // WelcomePage--------------------------------------------------------------------------------------

    worker->moveToThread(thread);
    thread->start();
    emit signal_worker_wait_connection();
    // Текущая страница
    //ui->stackedWidget->setCurrentIndex(2);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_worker_flashDriveFound(bool status)
{
    if(status && flags[0]) return;
    if(status != flags[0]) flags[0] = status;
    if(status){
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        signal_wpage_restart();
        ui->stackedWidget->setCurrentIndex(0);
    }
}


/*void MainWindow::slot_worker_dataIsReady()
{
    QFile file("/tmp/ecoprint_file_structure");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    qint32 size;
    in >> size;
    for(int i = 0; i < int(size); i++){
        QString str;
        in >> str;
        qDebug() << str;
    }
    ui->stackedWidget->setCurrentIndex(1);
}*/

void MainWindow::slot_wpage_button_pressed()
{
    qDebug() << "slot_wpage_button_pressed";
}


