#include "usbworker.h"

#include <QList>
#include <QDir>
#include <QtCore>
#include <QFile>
#include <QDataStream>
#include <QThread>
#include <string>
#include <cstdlib>

UsbWorker::UsbWorker()
{
    thread = new QThread(this);
    flag = 0;
    //connect(this, SIGNAL(destroyed()), thread, SLOT(quit()));
}

/// Запись данных в файл
bool recordingInFile(const QString& fileName, QStringList data){
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        qint32 size = data.size();
        out << size;
        for(int i = 0; i < data.size(); i++){
            out << data.at(i);
        }
        file.close();
    }
    else return false;
    return true;
}

void UsbWorker::slot_wait()
{
    moveToThread(thread);
    connect(thread, SIGNAL(started()), this, SLOT(work_wait()));
    thread->start();
}

void UsbWorker::work_wait()
{
    while(1){
        thread->sleep(std::chrono::milliseconds(850));
        bool is_plugged = isTheFlashDrivePluggedIn();
        if(flag == is_plugged) continue;
        flag = is_plugged;
        if(is_plugged){
            emit signal_flashDriveFound(true);
        }
        else {
            emit signal_flashDriveFound(false);
        }
    }
}

/// Возвращает true, если была найдена флешка.
bool UsbWorker::isTheFlashDrivePluggedIn()
{
    return runCmd("ls /dev/sd*");
}

/// Возвращает true, если команда cmd выполнится без ошибок.
bool UsbWorker::runCmd(const std::string &cmd)
{
    int status = std::system(cmd.c_str());
    if(WEXITSTATUS(status) == 0) return 1;
    return 0;
}

/// Возвращает список папок и pdf-файлов на флешке в указаной директории
/// (Если флешка не воткнута, то возвращает пустой список)
QStringList UsbWorker::getTheFileStructureOfTheDir(const QString &path)
{
    if(!isTheFlashDrivePluggedIn()){
        QStringList finfo;
        return finfo;
    }
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList filters;
    filters << "*.pdf" << "*.PDF";
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Size | QDir::Reversed);
    return dir.entryList();
}

/// Обрабатывает текст с консоли для findThePathToTheMountedFlashDrive
QString UsbWorker::processCmdOutput(const QString &cmd_line)
{
    QString res;

    if(cmd_line.contains("sda")){
        return cmd_line.mid(5);
    }
    return "";
}

/// Возвращает путь к флешке или пустую строку
QStringList UsbWorker::findThePathToTheMountedFlashDrive()
{
    if(!isTheFlashDrivePluggedIn()){
        QStringList finfo;
        return finfo;
    }
    runCmd("lsblk -rno name,size,mountpoint,fstype | awk 'NF==4 {print $1, $3}' > /tmp/ecoprint_cmdout");

    QFile file("/tmp/ecoprint_cmdout");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QStringList finfo;
        return finfo;
    }
    QTextStream in(&file);
    QStringList path;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QString tmp = processCmdOutput(line);
        if(tmp != "") path.append(tmp);
    }
    file.close();

    return path;
}
