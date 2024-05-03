#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usbworker.h"
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    // Слоты для работы с объектом UsbWorker+
    void slot_worker_flashDriveFound(bool);
    // Слоты для работы с объектом UsbWorker-

    // Слоты для работы с объектом WelcomePage+
    void slot_wpage_button_pressed();
    // Слоты для работы с объектом WelcomePage-
signals:    
    // Сигналы для работы с объектом UsbWorker+
    void signal_worker_run_usb();
    void signal_worker_wait_connection();
    // Сигналы для работы с объектом UsbWorker-

    // Сигналы для работы с объектом WelcomePage+
    void signal_wpage_restart();
    // Сигналы для работы с объектом WelcomePage-


private:
    Ui::MainWindow *ui;
    UsbWorker *worker;
    QThread *thread;
    bool *flags;
};
#endif // MAINWINDOW_H
